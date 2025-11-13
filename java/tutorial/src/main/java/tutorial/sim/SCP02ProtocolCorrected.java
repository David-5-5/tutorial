package tutorial.sim;

import javax.smartcardio.*;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.List;

public class SCP02ProtocolCorrected {
    
    // 配置参数
    private static final byte[] SCP02_MASTER_KEY = {
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
        0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
    };
    
    private static final byte[] AID = {
        (byte) 0xD1, 0x56, 0x00, 0x01, 0x01, 0x00, 0x01, 0x60,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
    };
    
    // 会话密钥
    private byte[] encKey = new byte[16];
    private byte[] macKey = new byte[16];
    private byte[] dekKey = new byte[16];
    
    // SCP02参数
    private byte[] hostChallenge = new byte[8];
    private byte[] cardChallenge = new byte[8];
    private byte[] sequenceCounter = new byte[2];
    
    private SecureRandom random = new SecureRandom();
    private CardChannel channel;
    
    /**
     * 初始化读卡器连接
     */
    public boolean connectToReader() {
        try {
            System.out.println("=== 初始化读卡器连接 ===");
            
            TerminalFactory factory = TerminalFactory.getDefault();
            CardTerminals terminals = factory.terminals();
            
            List<CardTerminal> terminalList = terminals.list();
            if (terminalList.isEmpty()) {
                System.out.println("未找到读卡器");
                return false;
            }
            
            CardTerminal terminal = terminalList.get(0);
            System.out.println("找到读卡器: " + terminal.getName());
            
            System.out.println("请插入SIM卡...");
            terminal.waitForCardPresent(30000);
            
            Card card = terminal.connect("T=0");
            channel = card.getBasicChannel();
            
            System.out.println("成功连接到SIM卡，ATR: " + bytesToHex(card.getATR().getBytes()));
            return true;
            
        } catch (CardException e) {
            System.out.println("读卡器连接失败: " + e.getMessage());
            return false;
        } catch (Exception e) {
            System.out.println("连接异常: " + e.getMessage());
            return false;
        }
    }
    
    /**
     * 发送APDU命令并获取响应
     */
    private ResponseAPDU sendAPDU(byte[] command) {
        try {
            CommandAPDU cmd = new CommandAPDU(command);
            System.out.println("发送: " + bytesToHex(command));
            
            ResponseAPDU response = channel.transmit(cmd);
            System.out.println("响应: " + bytesToHex(response.getBytes()));
            
            return response;
            
        } catch (CardException e) {
            System.out.println("APDU传输失败: " + e.getMessage());
            return null;
        }
    }
    
    /**
     * 处理61XX状态字 - 发送GET RESPONSE
     */
    private byte[] handle61Response(ResponseAPDU response) {
        try {
            if (response.getSW1() != 0x61) {
                return null;
            }
            
            int length = response.getSW2();
            System.out.println("需要GET RESPONSE获取 " + length + " 字节数据");
            
            // 发送GET RESPONSE命令
            byte[] getResponseCmd = new byte[] {
                0x00, (byte) 0xC0, 0x00, 0x00, (byte) length
            };
            
            ResponseAPDU getResponse = sendAPDU(getResponseCmd);
            if (getResponse != null && getResponse.getSW() == 0x9000) {
                return getResponse.getData();
            }
            
            return null;
            
        } catch (Exception e) {
            System.out.println("处理61响应异常: " + e.getMessage());
            return null;
        }
    }
    
    /**
     * 选择安全域
     */
    public boolean selectSecurityDomain() {
        try {
            System.out.println("\n=== 选择安全域 ===");
            
            byte[] selectCommand = new byte[5 + AID.length];
            selectCommand[0] = 0x00; // CLA
            selectCommand[1] = (byte) 0xA4; // INS
            selectCommand[2] = 0x04; // P1
            selectCommand[3] = 0x00; // P2
            selectCommand[4] = (byte) AID.length; // Lc
            System.arraycopy(AID, 0, selectCommand, 5, AID.length);
            
            ResponseAPDU response = sendAPDU(selectCommand);
            if (response == null) {
                return false;
            }
            
            // 处理61XX响应
            if (response.getSW1() == 0x61) {
                byte[] data = handle61Response(response);
                return data != null;
            }
            
            return response.getSW() == 0x9000;
            
        } catch (Exception e) {
            System.out.println("选择安全域异常: " + e.getMessage());
            return false;
        }
    }
    
    /**
     * 执行INITIALIZE UPDATE - 修复数组边界问题
     */
    public boolean initializeUpdate() {
        try {
            System.out.println("\n=== INITIALIZE UPDATE ===");
            
            // 动态生成主机挑战
            random.nextBytes(hostChallenge);
            System.out.println("生成主机挑战: " + bytesToHex(hostChallenge));
            
            // 严格按照工具格式: 80 50 00 00 08 [HostChallenge]
            byte[] command = new byte[13];
            command[0] = (byte) 0x80; // CLA
            command[1] = (byte) 0x50; // INS
            command[2] = (byte) 0x00; // P1
            command[3] = (byte) 0x00; // P2
            command[4] = (byte) 0x08; // Lc
            System.arraycopy(hostChallenge, 0, command, 5, 8);
            
            ResponseAPDU response = sendAPDU(command);
            if (response == null) {
                return false;
            }
            
            // 处理61XX响应
            byte[] data;
            if (response.getSW1() == 0x61) {
                data = handle61Response(response);
            } else if (response.getSW() == 0x9000) {
                data = response.getData();
            } else {
                System.out.println("INITIALIZE UPDATE命令失败");
                return false;
            }
            
            if (data == null || data.length < 22) {
                System.out.println("响应数据长度不足，期望至少22字节，实际: " + (data != null ? data.length : 0));
                return false;
            }
            
            // 解析响应数据
            System.out.println("解析INITIALIZE UPDATE响应:");
            System.out.println("完整数据: " + bytesToHex(data));
            
            // 安全地解析数据
            byte[] keyDiversificationData = Arrays.copyOfRange(data, 0, 10);
            byte keyVersion = data[10];
            byte scpImplementation = data[11];
            System.arraycopy(data, 12, sequenceCounter, 0, 2);
            System.arraycopy(data, 14, cardChallenge, 0, 8);
            
            System.out.println("密钥版本: " + String.format("%02X", keyVersion));
            System.out.println("SCP实现: " + String.format("%02X", scpImplementation));
            System.out.println("序列计数器: " + bytesToHex(sequenceCounter));
            System.out.println("卡挑战: " + bytesToHex(cardChallenge));
            
            // 如果数据长度足够，解析卡密码
            if (data.length >= 30) {
                byte[] cardCryptogram = Arrays.copyOfRange(data, 22, 30);
                System.out.println("卡密码: " + bytesToHex(cardCryptogram));
            }
            
            // 派生会话密钥
            deriveSessionKeys(keyDiversificationData);
            
            return true;
            
        } catch (Exception e) {
            System.out.println("INITIALIZE UPDATE异常: " + e.getMessage());
            e.printStackTrace();
            return false;
        }
    }
    
    /**
     * 派生会话密钥 - 简化的SCP02密钥派生
     */
    private void deriveSessionKeys(byte[] diversificationData) {
        try {
            // 简化的密钥派生 - 实际应根据GP规范实现完整派生
            // 这里直接使用主密钥作为会话密钥
            System.arraycopy(SCP02_MASTER_KEY, 0, encKey, 0, 16);
            System.arraycopy(SCP02_MASTER_KEY, 0, macKey, 0, 16);
            System.arraycopy(SCP02_MASTER_KEY, 0, dekKey, 0, 16);
            
            System.out.println("派生会话密钥完成:");
            System.out.println("ENC Key: " + bytesToHex(encKey));
            System.out.println("MAC Key: " + bytesToHex(macKey));
            
        } catch (Exception e) {
            throw new RuntimeException("密钥派生失败", e);
        }
    }
    
    /**
     * 将16字节密钥扩展为24字节3DES密钥
     */
    private byte[] expandKeyTo24Bytes(byte[] key16) {
        byte[] key24 = new byte[24];
        System.arraycopy(key16, 0, key24, 0, 16);
        System.arraycopy(key16, 0, key24, 16, 8); // 复制前8字节到末尾
        return key24;
    }
    
    /**
     * 计算C-MAC (SCP02规范) - 修正版本
     */
    private byte[] calculateCMAC(byte[] data) throws Exception {
        try {
            System.out.println("计算C-MAC:");
            System.out.println("输入数据: " + bytesToHex(data));
            System.out.println("MAC Key: " + bytesToHex(macKey));
            
            // 将16字节密钥扩展为24字节3DES密钥
            byte[] expandedKey = expandKeyTo24Bytes(macKey);
            System.out.println("扩展后的3DES Key: " + bytesToHex(expandedKey));
            
            // 使用3DES CBC模式
            Cipher cipher = Cipher.getInstance("DESede/CBC/NoPadding");
            SecretKeySpec keySpec = new SecretKeySpec(expandedKey, "DESede");
            IvParameterSpec iv = new IvParameterSpec(new byte[8]);
            
            // 数据填充 (ISO/IEC 9797-1 Method 2)
            byte[] paddedData = padData(data);
            System.out.println("填充后数据: " + bytesToHex(paddedData));
            
            cipher.init(Cipher.ENCRYPT_MODE, keySpec, iv);
            byte[] encrypted = cipher.doFinal(paddedData);
            System.out.println("加密结果: " + bytesToHex(encrypted));
            
            // 取最后8字节作为MAC
            byte[] mac = new byte[8];
            System.arraycopy(encrypted, encrypted.length - 8, mac, 0, 8);
            
            System.out.println("C-MAC: " + bytesToHex(mac));
            return mac;
            
        } catch (Exception e) {
            System.out.println("C-MAC计算失败: " + e.getMessage());
            throw e;
        }
    }
    
    /**
     * 数据填充
     */
    private byte[] padData(byte[] data) {
        int blockSize = 8;
        int paddingLength = blockSize - (data.length % blockSize);
        if (paddingLength == 0) paddingLength = blockSize;
        
        byte[] padded = new byte[data.length + paddingLength];
        System.arraycopy(data, 0, padded, 0, data.length);
        padded[data.length] = (byte) 0x80; // 起始填充字节
        
        // 其余部分自动初始化为0
        return padded;
    }
    
    /**
     * 执行EXTERNAL AUTHENTICATE - 修正版本，遵循SCP02协议
     */
    public boolean externalAuthenticate() {
        try {
            System.out.println("\n=== EXTERNAL AUTHENTICATE ===");
            
            // 1. 构建认证数据 (根据SCP02协议)
            // 数据包括: 主机挑战 + 卡挑战 + 序列计数器
            byte[] authenticationData = new byte[18]; // 8+8+2=18字节
            System.arraycopy(hostChallenge, 0, authenticationData, 0, 8);
            System.arraycopy(cardChallenge, 0, authenticationData, 8, 8);
            System.arraycopy(sequenceCounter, 0, authenticationData, 16, 2);
            
            // 2. 动态计算C-MAC
            byte[] mac = calculateCMAC(authenticationData);
            
            // 3. 构建EXTERNAL AUTHENTICATE命令数据
            // 根据SCP02协议，数据部分应该只包含MAC，不需要填充
            byte[] command = new byte[5 + 8]; // 8字节MAC
            command[0] = (byte) 0x84; // CLA (安全通道)
            command[1] = (byte) 0x82; // INS
            command[2] = (byte) 0x01; // P1 (安全级别)
            command[3] = (byte) 0x00; // P2
            command[4] = (byte) 0x08; // Lc (8字节)
            System.arraycopy(mac, 0, command, 5, 8);
            
            ResponseAPDU response = sendAPDU(command);
            if (response == null) {
                return false;
            }
            
            boolean success = response.getSW() == 0x9000;
            System.out.println("认证结果: " + (success ? "成功" : "失败"));
            return success;
            
        } catch (Exception e) {
            System.out.println("EXTERNAL AUTHENTICATE异常: " + e.getMessage());
            e.printStackTrace();
            return false;
        }
    }
    
    /**
     * 完整的SCP02协议流程
     */
    public boolean executeSCP02Protocol() {
        try {
            System.out.println("=== 开始SCP02协议交互 ===");
            
            // 1. 连接读卡器
            if (!connectToReader()) {
                return false;
            }
            
            // 2. 选择安全域
            if (!selectSecurityDomain()) {
                System.out.println("选择安全域失败");
                return false;
            }
            
            // 3. INITIALIZE UPDATE
            if (!initializeUpdate()) {
                System.out.println("INITIALIZE UPDATE失败");
                return false;
            }
            
            // 4. EXTERNAL AUTHENTICATE
            if (!externalAuthenticate()) {
                System.out.println("EXTERNAL AUTHENTICATE失败");
                return false;
            }
            
            System.out.println("\n=== SCP02协议交互完成 ===");
            return true;
            
        } catch (Exception e) {
            System.out.println("SCP02协议执行异常: " + e.getMessage());
            return false;
        }
    }
    
    /**
     * 字节数组转十六进制字符串
     */
    private static String bytesToHex(byte[] bytes) {
        if (bytes == null) return "null";
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02X ", b));
        }
        return sb.toString().trim();
    }
    
    public static void main(String[] args) {
        System.setProperty("sun.security.smartcardio.t0GetResponse", "false");
        System.setProperty("sun.security.smartcardio.t1GetResponse", "false");
        
        SCP02ProtocolCorrected scp02 = new SCP02ProtocolCorrected();
        boolean success = scp02.executeSCP02Protocol();
        
        System.out.println("\n最终结果: " + (success ? "SCP02认证成功" : "SCP02认证失败"));
    }
}