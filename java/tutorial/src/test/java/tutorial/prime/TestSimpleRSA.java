package tutorial.prime;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.math.BigInteger;

import org.junit.jupiter.api.Test;


public class TestSimpleRSA {

    @Test
    public void TestEncryptAndDecrpt() throws Exception {
        SimpleRSA rsa = SimpleRSA.newInstance();
        String plain = "hello";
        
        BigInteger chiper = rsa.enc(new BigInteger(plain.getBytes()));
        System.out.printf("chiper big integer is %o\n", chiper);
        
        BigInteger toPlain = rsa.dec(chiper);
        System.out.printf("decypted big integer is %o\n", toPlain);

        assertEquals(plain, new String(toPlain.toByteArray()));

    }

    @Test
    public void TestEncryptAndDecrptWithHighPrecision() throws Exception {
        SimpleRSA rsa = SimpleRSA.newInstance(4096, 200);
        String plain = "hello";
        
        BigInteger chiper = rsa.enc(new BigInteger(plain.getBytes()));
        System.out.printf("chiper big integer is %o\n", chiper);
        
        BigInteger toPlain = rsa.dec(chiper);
        System.out.printf("decypted big integer is %o\n", toPlain);

        assertEquals(plain, new String(toPlain.toByteArray()));

    }
}
