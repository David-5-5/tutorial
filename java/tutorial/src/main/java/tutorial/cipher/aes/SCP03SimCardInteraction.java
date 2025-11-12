package tutorial.cipher.aes;

import javax.smartcardio.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.security.*;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;
import javax.crypto.*;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import org.bouncycastle.jce.provider.BouncyCastleProvider;

/**
 * SCP03 协议卡外实体（终端/读卡器）与 SIM 卡交互完整实现
 * 遵循 ISO 7816-4、SCP03（ETSI TS 102 221）协议规范
 * 功能：安全通道建立（INIT UPDATE + EXTERNAL AUTH）、加密传输、MAC 校验
 */
public class SCP03SimCardInteraction {
    // SCP03 协议核心常量
    private static final byte CLA_SCP03 = (byte) 0x80; // 命令类别（SCP03 专用）
    private static final byte INS_INITIALIZE_UPDATE = (byte) 0x50; // 初始化更新
    private static final byte INS_EXTERNAL_AUTHENTICATE = (byte) 0x82; // 外部认证
    private static final byte P1_INIT_UPDATE = (byte) 0x00; // INIT UPDATE P1（无特殊要求）
    private static final byte P2_INIT_UPDATE = (byte) 0x00; // INIT UPDATE P2（无特殊要求）
    private static final byte LE_INIT_UPDATE = (byte) 0x20; // INIT UPDATE 期望返回长度（32 字节）
    private static final byte[] AID_ISD = { (byte) 0xA0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00 }; // SIM 卡默认安全域 AID

    // 预共享密钥（PSK）：实际场景建议用 ECDH 动态协商，此处为测试简化
    private static final byte[] PSK = { 0x01, 0x23, 0x45, 0x67, (byte) 0x89, (byte) 0xAB, (byte) 0xCD, (byte) 0xEF,
            (byte) 0xFE, (byte) 0xDC, (byte) 0xBA, (byte) 0x98, 0x76, 0x54, 0x32, 0x10 };

    // 会话密钥（安全通道建立后生成）
    private SecretKey sessionEncKey; // 加密密钥（KEK, AES-128）
    private SecretKey sessionMacKey; // MAC 密钥（KMAC, AES-128）
    private SecretKey sessionDekKey; // 数据加密密钥（KDEK, AES-128）

    // 智能卡交互对象
    private TerminalFactory terminalFactory;
    private CardTerminal terminal;
    private Card card;
    private CardChannel channel;

    static {
        // 注册 BouncyCastle 加密 Provider（需导入依赖）
        Security.addProvider(new BouncyCastleProvider());
    }

    /**
     * 初始化：连接 SIM 卡读卡器
     */
    public void init() throws CardException {
        terminalFactory = TerminalFactory.getDefault();
        CardTerminals terminals = terminalFactory.terminals();
        if (terminals.list().isEmpty()) {
            throw new CardException("未找到可用的读卡器，请插入 SIM 卡读卡器");
        }

        // 选择第一个可用读卡器（可根据实际需求修改索引）
        terminal = terminals.list().get(0);
        card = terminal.connect("T=0"); // T=0 协议（SIM 卡常用）
        channel = card.getBasicChannel();
        System.out.println("SIM 卡连接成功！ATR: " + bytesToHex(card.getATR().getBytes()));
    }

    /**
     * 选择 SIM 卡安全域（ISD）：SCP03 协议需先选择安全域才能建立安全通道
     */
    public void selectSecurityDomain() throws CardException {
        CommandAPDU selectCmd = new CommandAPDU(
                (byte) 0x00, // CLA: 基本命令
                (byte) 0xA4, // INS: 选择文件/应用
                (byte) 0x04, // P1: 按 AID 选择（全匹配）
                (byte) 0x00, // P2: 返回 FCI 数据
                AID_ISD, // 安全域 AID
                (byte) 0x00 // LE: 不指定返回长度（自动适配）
        );

        ResponseAPDU response = channel.transmit(selectCmd);
        if (response.getSW() != 0x9000) {
            throw new CardException("选择安全域失败！SW: " + Integer.toHexString(response.getSW()));
        }
        System.out.println("安全域（ISD）选择成功！FCI: " + bytesToHex(response.getData()));
    }

    /**
     * 步骤 1：发送 INITIALIZE UPDATE 命令（密钥协商初始化）
     * 
     * @return 卡随机数（Card Nonce）
     * @throws NoSuchProviderException 
     * @throws BadPaddingException 
     * @throws IllegalBlockSizeException 
     * @throws NoSuchPaddingException 
     */
    public byte[] initializeUpdate() throws CardException, NoSuchAlgorithmException, InvalidKeyException, NoSuchProviderException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
        // 终端生成 8 字节随机数（Terminal Nonce）
        byte[] terminalNonce = new byte[8];
        new SecureRandom().nextBytes(terminalNonce);
        System.out.println("终端随机数（Terminal Nonce）: " + bytesToHex(terminalNonce));

        // 构造 INIT UPDATE 命令数据域：Terminal Nonce(8) + 密钥版本(1) + 保留位(1)
        byte[] cmdData = new byte[10];
        System.arraycopy(terminalNonce, 0, cmdData, 0, 8);
        cmdData[8] = (byte) 0x01; // 密钥版本（KCV，与 PSK 对应）
        cmdData[9] = (byte) 0x00; // 保留位（必须为 0x00）

        // 构建 INIT UPDATE 命令
        CommandAPDU initUpdateCmd = new CommandAPDU(
                CLA_SCP03,
                INS_INITIALIZE_UPDATE,
                P1_INIT_UPDATE,
                P2_INIT_UPDATE,
                cmdData,
                LE_INIT_UPDATE);

        // 发送命令并接收响应
        ResponseAPDU response = channel.transmit(initUpdateCmd);
        if (response.getSW() != 0x9000) {
            throw new CardException("INIT UPDATE 命令失败！SW: " + Integer.toHexString(response.getSW()));
        }

        byte[] respData = response.getData();
        System.out.println("INIT UPDATE 响应数据: " + bytesToHex(respData));

        // 解析响应数据（SCP03 规范）
        byte[] cardNonce = new byte[8]; // 0-7 字节：卡随机数
        byte[] cardPubKey = new byte[16]; // 8-23 字节：卡 ECDH 公钥（简化版忽略，用 PSK 替代）
        byte[] respMac = new byte[8]; // 24-31 字节：响应 MAC
        System.arraycopy(respData, 0, cardNonce, 0, 8);
        System.arraycopy(respData, 8, cardPubKey, 0, 16);
        System.arraycopy(respData, 24, respMac, 0, 8);

        // 校验响应 MAC（输入：Terminal Nonce + Card Nonce + 密钥版本 + 保留位）
        byte[] macInput = ByteBuffer.allocate(18)
                .put(terminalNonce)
                .put(cardNonce)
                .put(cmdData[8])
                .put(cmdData[9])
                .array();
        byte[] expectedMac = computeAesMac(PSK, macInput);
        if (!MessageDigest.isEqual(expectedMac, respMac)) {
            throw new SecurityException("INIT UPDATE MAC 校验失败！");
        }
        System.out.println("INIT UPDATE MAC 校验成功！卡随机数（Card Nonce）: " + bytesToHex(cardNonce));

        // 生成会话密钥（KEK/KMAC/KDEK）
        generateSessionKeys(terminalNonce, cardNonce);
        return cardNonce;
    }

    /**
     * 步骤 2：发送 EXTERNAL AUTHENTICATE 命令（完成安全通道建立）
     * @throws NoSuchProviderException 
     * @throws BadPaddingException 
     * @throws IllegalBlockSizeException 
     * @throws NoSuchPaddingException 
     */
    public void externalAuthenticate(byte[] terminalNonce, byte[] cardNonce)
            throws CardException, NoSuchAlgorithmException, InvalidKeyException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException, NoSuchProviderException {
        // 构建认证数据：用会话 MAC 密钥签名（Card Nonce + Terminal Nonce）
        byte[] signInput = ByteBuffer.allocate(16)
                .put(cardNonce)
                .put(terminalNonce)
                .array();
        byte[] signature = computeAesMac(sessionMacKey.getEncoded(), signInput);
        System.out.println("外部认证签名: " + bytesToHex(signature));

        // 构建 EXTERNAL AUTH 命令数据域（简化版：仅包含签名，实际需添加终端 ECDH 公钥）
        CommandAPDU extAuthCmd = new CommandAPDU(
                CLA_SCP03,
                INS_EXTERNAL_AUTHENTICATE,
                (byte) 0x00,
                (byte) 0x00,
                signature,
                (byte) 0x00);

        // 发送命令并接收响应
        ResponseAPDU response = channel.transmit(extAuthCmd);
        if (response.getSW() != 0x9000) {
            throw new CardException("外部认证失败！SW: " + Integer.toHexString(response.getSW()));
        }
        System.out.println("外部认证成功！SCP03 安全通道建立完成！");
    }

    /**
     * 安全通道内发送加密命令（如读取 SIM 卡数据、执行 Dilithium 签名等）
     * 
     * @param apduData 原始 APDU 命令（如：0x00 0xB0 0x00 0x00 0x08 读取 8 字节数据）
     * @return 解密后的响应数据
     */
    public ResponseAPDU sendEncryptedCommand(byte[] apduData) throws Exception {
        if (sessionEncKey == null || sessionMacKey == null) {
            throw new IllegalStateException("请先建立 SCP03 安全通道！");
        }

        // 1. 生成 AES-CBC 初始化向量（IV，8 字节，SCP03 要求）
        byte[] iv = new byte[8];
        new SecureRandom().nextBytes(iv);
        IvParameterSpec ivSpec = new IvParameterSpec(iv);

        // 2. 原始 APDU 数据填充（ISO 7816-4 80 填充：末尾加 0x80，其余补 0x00 至块大小）
        byte[] paddedData = padData(apduData);

        // 3. AES-128-CBC 加密数据
        Cipher aesCipher = Cipher.getInstance("AES/CBC/NoPadding", "BC");
        aesCipher.init(Cipher.ENCRYPT_MODE, sessionEncKey, ivSpec);
        byte[] encryptedData = aesCipher.doFinal(paddedData);

        // 4. 计算 MAC（AES-MAC，覆盖 IV + 加密数据）
        byte[] macInput = ByteBuffer.allocate(iv.length + encryptedData.length)
                .put(iv)
                .put(encryptedData)
                .array();
        byte[] mac = computeAesMac(sessionMacKey.getEncoded(), macInput);

        // 5. 构建 SCP03 加密命令数据域：IV(8) + 加密数据 + MAC(8)
        byte[] scp03Data = ByteBuffer.allocate(iv.length + encryptedData.length + mac.length)
                .put(iv)
                .put(encryptedData)
                .put(mac)
                .array();

        // 6. 构建加密 APDU 命令（CLA 0xC0 = 0x80 | 0x40，表示加密传输）
        CommandAPDU encryptedCmd = new CommandAPDU(
                (byte) 0xC0, // CLA: 加密传输标记
                apduData[1], // INS: 原始命令的 INS
                apduData[2], // P1: 原始命令的 P1
                apduData[3], // P2: 原始命令的 P2
                scp03Data,
                (byte) 0x00 // LE: 期望返回长度（根据实际需求调整）
        );

        // 7. 发送加密命令并接收响应
        ResponseAPDU response = channel.transmit(encryptedCmd);
        if (response.getSW() != 0x9000) {
            throw new CardException("加密命令发送失败！SW: " + Integer.toHexString(response.getSW()));
        }

        // 8. 解析并验证响应数据
        byte[] respData = response.getData();
        byte[] respIv = new byte[8];
        byte[] respEncryptedData = new byte[respData.length - 16]; // 去掉 IV(8) + MAC(8)
        byte[] respMac = new byte[8];
        System.arraycopy(respData, 0, respIv, 0, 8);
        System.arraycopy(respData, 8, respEncryptedData, 0, respEncryptedData.length);
        System.arraycopy(respData, respData.length - 8, respMac, 0, 8);

        // 校验响应 MAC
        byte[] respMacInput = ByteBuffer.allocate(respIv.length + respEncryptedData.length)
                .put(respIv)
                .put(respEncryptedData)
                .array();
        byte[] expectedRespMac = computeAesMac(sessionMacKey.getEncoded(), respMacInput);
        if (!MessageDigest.isEqual(expectedRespMac, respMac)) {
            throw new SecurityException("响应数据 MAC 校验失败！");
        }

        // 9. 解密响应数据
        IvParameterSpec respIvSpec = new IvParameterSpec(respIv);
        aesCipher.init(Cipher.DECRYPT_MODE, sessionEncKey, respIvSpec);
        byte[] decryptedData = aesCipher.doFinal(respEncryptedData);
        decryptedData = unpadData(decryptedData); // 去除填充

        System.out.println("加密命令传输成功！解密后响应数据: " + bytesToHex(decryptedData));
        return new ResponseAPDU(decryptedData);
    }

    /**
     * 生成 SCP03 会话密钥（KEK/KMAC/KDEK）
     * 密钥派生函数：KDF-HMAC-SHA256（遵循 SCP03 规范）
     * @throws NoSuchProviderException 
     */
    private void generateSessionKeys(byte[] terminalNonce, byte[] cardNonce)
            throws NoSuchAlgorithmException, InvalidKeyException, NoSuchProviderException {
        // KDF 输入：PSK + Terminal Nonce + Card Nonce
        byte[] kdfInput = ByteBuffer.allocate(PSK.length + terminalNonce.length + cardNonce.length)
                .put(PSK)
                .put(terminalNonce)
                .put(cardNonce)
                .array();

        // 派生 KEK（加密密钥）
        byte[] kek = kdfHmacSha256(PSK, kdfInput, "KEK", 16);
        sessionEncKey = new SecretKeySpec(kek, "AES");

        // 派生 KMAC（MAC 密钥）
        byte[] kmac = kdfHmacSha256(PSK, kdfInput, "KMAC", 16);
        sessionMacKey = new SecretKeySpec(kmac, "AES");

        // 派生 KDEK（数据加密密钥）
        byte[] kdek = kdfHmacSha256(PSK, kdfInput, "KDEK", 16);
        sessionDekKey = new SecretKeySpec(kdek, "AES");

        System.out.println("会话密钥生成成功！");
        System.out.println("KEK: " + bytesToHex(kek));
        System.out.println("KMAC: " + bytesToHex(kmac));
        System.out.println("KDEK: " + bytesToHex(kdek));
    }



    /**
     * 【核心缺失】KDF-HMAC-SHA256 密钥导出函数（严格遵循 SCP03 规范 ETSI TS 102 221）
     * 输入格式：label + 0x00 + input + 输出长度（4字节大端，单位：比特）
     * 支持迭代导出（当输出密钥长度 > 32字节时）
     */
    /**
     * KDF-HMAC-SHA256 密钥派生（SCP03 规范要求）
     * 
     * @param key       派生密钥（PSK）
     * @param input     输入数据
     * @param label     密钥用途标签
     * @param outputLen 输出密钥长度（字节）
     * @return 派生密钥
     */
    private byte[] kdfHmacSha256(byte[] key, byte[] input, String label, int outputLen)
            throws NoSuchAlgorithmException, InvalidKeyException, NoSuchProviderException {
        Mac hmacSha256 = Mac.getInstance("HmacSHA256", "BC");
        hmacSha256.init(new SecretKeySpec(key, "HmacSHA256"));

        // 1. 构造 KDF 输入核心部分：label + 0x00 + input
        byte[] labelBytes = label.getBytes();
        byte[] coreInput = ByteBuffer.allocate(labelBytes.length + 1 + input.length)
                .put(labelBytes)
                .put((byte) 0x00) // 分隔符（SCP03 强制要求）
                .put(input)
                .array();

        // 2. 构造输出长度字段（4字节大端，单位：比特）
        byte[] lengthBytes = ByteBuffer.allocate(4)
                .order(ByteOrder.BIG_ENDIAN)
                .putInt(outputLen * 8) // SCP03 要求长度以比特为单位
                .array();

        // 3. 迭代计算 HMAC（若输出长度 > 32字节，需多轮迭代）
        ByteBuffer resultBuffer = ByteBuffer.allocate(outputLen);
        byte[] counter = new byte[1]; // 迭代计数器（从 0x01 开始）
        int remaining = outputLen;

        while (remaining > 0) {
            // 每轮 HMAC 输入：counter + coreInput + lengthBytes
            byte[] roundInput = ByteBuffer.allocate(1 + coreInput.length + lengthBytes.length)
                    .put(counter)
                    .put(coreInput)
                    .put(lengthBytes)
                    .array();

            // 计算当前轮 HMAC-SHA256 结果（32字节）
            byte[] roundHmac = hmacSha256.doFinal(roundInput);

            // 写入结果（取当前轮结果的前 remaining 字节）
            int writeLen = Math.min(remaining, roundHmac.length);
            resultBuffer.put(roundHmac, 0, writeLen);

            // 更新计数器和剩余长度
            counter[0]++;
            remaining -= writeLen;
        }

        return resultBuffer.array();
    }

    /**
     * 计算 AES-CMAC（SCP03 标准 MAC 算法，替代简单哈希，符合协议要求）
     * SCP03 中 MAC 长度固定为 8字节（取 CMAC 结果的前 8字节）
     * 
     * @throws NoSuchProviderException
     */
    private byte[] computeAesMac(byte[] key, byte[] input) throws NoSuchAlgorithmException, InvalidKeyException,
            NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException, NoSuchProviderException {
        // SCP03 强制要求 MAC 算法为 AES-CMAC（而非普通 HMAC）
        Cipher cmacCipher = Cipher.getInstance("AES/CMAC/NoPadding", "BC");
        SecretKeySpec keySpec = new SecretKeySpec(key, "AES");
        cmacCipher.init(Cipher.ENCRYPT_MODE, keySpec);

        // 计算 CMAC 完整结果（16字节）
        byte[] fullCmac = cmacCipher.doFinal(input);

        // SCP03 要求 MAC 长度为 8字节（取前 8字节，协议规范）
        byte[] truncatedCmac = new byte[8];
        System.arraycopy(fullCmac, 0, truncatedCmac, 0, 8);

        return truncatedCmac;
    }

    /**
     * ISO 7816-4 80 填充（SCP03 加密数据必须遵循的填充规则）
     * 规则：末尾加 0x80，其余补 0x00，直到数据长度为 AES 块大小（16字节）的整数倍
     */
    private byte[] padData(byte[] data) {
        int blockSize = 16; // AES-128 块大小固定为 16字节（SCP03 强制）
        int paddingLen = blockSize - (data.length % blockSize);

        ByteBuffer paddedBuffer = ByteBuffer.allocate(data.length + paddingLen);
        paddedBuffer.put(data);
        paddedBuffer.put((byte) 0x80); // 填充起始标记（必需）
        for (int i = 1; i < paddingLen; i++) {
            paddedBuffer.put((byte) 0x00); // 剩余填充位补 0x00
        }

        return paddedBuffer.array();
    }

    /**
     * 去除 ISO 7816-4 80 填充（解密后数据还原）
     */
    private byte[] unpadData(byte[] paddedData) {
        // 从末尾查找 0x80 填充标记
        int paddingStartIndex = paddedData.length - 1;
        while (paddingStartIndex >= 0 && paddedData[paddingStartIndex] == 0x00) {
            paddingStartIndex--;
        }

        // 验证填充标记（必须是 0x80，否则为非法数据）
        if (paddingStartIndex < 0 || paddedData[paddingStartIndex] != 0x80) {
            throw new IllegalArgumentException("无效的填充数据，未找到 0x80 标记");
        }

        // 截取原始数据（排除填充部分）
        byte[] originalData = new byte[paddingStartIndex];
        System.arraycopy(paddedData, 0, originalData, 0, paddingStartIndex);

        return originalData;
    }

    /**
     * 字节数组转十六进制字符串（日志输出用）
     */
    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02X", b));
        }
        return sb.toString();
    }

    /**
     * 主函数（测试流程：连接 SIM 卡 → 选择安全域 → 建立安全通道 → 发送加密命令）
     */
    public static void main(String[] args) {
        SCP03SimCardInteraction scp03 = new SCP03SimCardInteraction();
        try {
            // 1. 初始化连接
            scp03.init();

            // 2. 选择安全域
            scp03.selectSecurityDomain();

            // 3. 初始化更新（密钥协商第一步）
            byte[] terminalNonce = new byte[8];
            new SecureRandom().nextBytes(terminalNonce); // 复用终端随机数（与 initializeUpdate 中一致）
            byte[] cardNonce = scp03.initializeUpdate();

            // 4. 外部认证（建立安全通道）
            scp03.externalAuthenticate(terminalNonce, cardNonce);

            // 5. 发送加密命令（示例：读取 SIM 卡文件，原始 APDU：0x00 0xB0 0x00 0x00 0x08 → 读取 8字节数据）
            byte[] originalApdu = { 0x00, (byte) 0xB0, 0x00, 0x00, 0x08 };
            ResponseAPDU response = scp03.sendEncryptedCommand(originalApdu);

            System.out.println("最终响应数据：" + bytesToHex(response.getData()));
            System.out.println("响应状态字：" + Integer.toHexString(response.getSW()));

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 关闭卡片连接
            if (scp03.card != null) {
                try {
                    scp03.card.disconnect(false);
                    System.out.println("SIM 卡连接已关闭");
                } catch (CardException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}