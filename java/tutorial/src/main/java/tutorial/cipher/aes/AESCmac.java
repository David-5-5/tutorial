package tutorial.cipher.aes;

import java.security.Security;
import java.util.Arrays;

import org.bouncycastle.crypto.macs.CMac;
import org.bouncycastle.crypto.params.KeyParameter;
import org.bouncycastle.jce.provider.BouncyCastleProvider;

public class AESCmac {
    public static String keyString = "606162636465666768696A6B6C6D6E6F";// 固定密钥
    public static String msg = "003815163A2222B000B1000000002E0C0114FF98FDF620C194358C2657BBE12B917D0BE572050000000000000000000000000000000000000000000000000000";

    static {
        // 添加 Bouncy Castle 作为安全提供者
        if (Security.getProvider("BC") == null) {
            Security.addProvider(new BouncyCastleProvider());
        }
    }

    // 得到加密后数据 MAC
    public static byte[] Aes_Cmac(byte[] key, byte[] message) {

        // 将密钥K转换为KeyParameter类型
        KeyParameter keyParam = new KeyParameter(key);

        // 创建CMAC对象，使用AES算法
        CMac cmac = new CMac(new org.bouncycastle.crypto.engines.AESEngine(), 16 * 8); // AES-128
        cmac.init(keyParam);

        // 进行CMAC处理
        cmac.update(message, 0, message.length);

        // 获取计算出的MAC值
        byte[] mac = new byte[cmac.getMacSize()];
        cmac.doFinal(mac, 0);

        return mac;
    }

    public static void main(String[] args) throws Exception {
        byte[] key = hexStrtoByte(keyString); // 密钥
        byte[] message = hexStrtoByte(msg);

        // 使用AES-CMAC进行加密（实际是消息认证）
        byte[] Encrypt = Aes_Cmac(key, message);
        System.out.println(bytesToHex(Encrypt));

        // 在这里发送27 02 + Encrypt 给ECU，并接收ECU计算的 Encrypt1并进行比较...

        // 省略了网络通信部分,仅保留逻辑核心（模拟67 02 ECU的比较过程）
        byte[] Encrypt1FromECU = receiveEncryptedCMACFromECU();
        System.out.println(bytesToHex(Encrypt1FromECU));

        // 比较两个加密后的数据是否一致
        boolean isMatch = Arrays.equals(Encrypt, Encrypt1FromECU);
        if (isMatch) {
            System.out.println("验证成功，返回67 02");
        } else {
            System.out.println("验证失败，返回NRC 35 36");
        }
    }

    // 辅助方法：模拟从ECU接收加密后的 CMAC（此处假设）
    private static byte[] receiveEncryptedCMACFromECU() {
        // 实际情况下，这应该是通过网络通信接收到的数据
        // 此处仅为示例，返回一个假定的CMAC结果
        byte[] key = hexStrtoByte(keyString);
        byte[] message = hexStrtoByte(msg);
        return Aes_Cmac(key, message);
    }

    // bytes --> 16进制
    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    /**
     * 十六进制字符串转换 bytes
     */
    public static byte[] hexStrtoByte(String hexStr) {
        byte[] bytes = new byte[hexStr.length() / 2];
        for (int i = 0; i < hexStr.length(); i += 2) {
            bytes[i / 2] = (byte) Integer.parseInt(hexStr.substring(i, i + 2), 16);
        }
        return bytes;
    }
}
