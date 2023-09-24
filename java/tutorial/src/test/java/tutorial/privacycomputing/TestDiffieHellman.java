package tutorial.privacycomputing;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import java.math.BigInteger;

import org.junit.jupiter.api.Test;

public class TestDiffieHellman {

    @Test
    public void TestSharedKey() {
        BaseDiffieHellman base = BaseDiffieHellman.newInstance();
        DiffieHellman partA = DiffieHellman.newInstance(base);
        DiffieHellman partB = DiffieHellman.newInstance(base);

        assertNotEquals(partA.getPublic(), partB.getPublic());
        BigInteger key = partA.shareSecretKey(partB.getPublic());
        assertEquals(key, partB.shareSecretKey(partA.getPublic()));

        // do some times
        assertEquals(key, partB.shareSecretKey(partA.getPublic()));
        assertEquals(key, partA.shareSecretKey(partB.getPublic()));
        assertEquals(partA.shareSecretKey(partB.getPublic()), partB.shareSecretKey(partA.getPublic()));
    }

    @Test
    public void TestSharedKeyWithReset() {
        BaseDiffieHellman base = BaseDiffieHellman.newInstance();
        DiffieHellman partA = DiffieHellman.newInstance(base);
        DiffieHellman partB = DiffieHellman.newInstance(base);

        assertNotEquals(partA.getPublic(), partB.getPublic());
        BigInteger key = partA.shareSecretKey(partB.getPublic());
        assertEquals(key, partB.shareSecretKey(partA.getPublic()));

        // do some times
        partA.resetPrivate();
        partB.resetPrivate();
        assertNotEquals(key, partB.shareSecretKey(partA.getPublic()));
        assertNotEquals(key, partA.shareSecretKey(partB.getPublic()));
        assertNotEquals(partA.getPublic(), partB.getPublic());
        assertEquals(partA.shareSecretKey(partB.getPublic()), partB.shareSecretKey(partA.getPublic()));
        assertEquals(partA.shareSecretKey(partB.getPublic()), partB.shareSecretKey(partA.getPublic()));
    }

    @Test
    public void TestSharedKeyWithStability() {
        int[] bits_a = { 256, 256, 512, 512, 1024, 1024, 2048, 2048, 4096, 4096 };
        int[] certainty_a = { 20, 50, 50, 100, 100, 150, 150, 200, 200, 300 };
        Long begin = System.currentTimeMillis();
        int ins_c = 1, reset_c = 10;
        for (int inx = 0; inx < 10; inx++) {
            begin = System.currentTimeMillis();
            for (int i = 0; i < ins_c; i++) {
                BaseDiffieHellman base = BaseDiffieHellman.newInstance(bits_a[inx], certainty_a[inx]);
                DiffieHellman partA = DiffieHellman.newInstance(base);
                DiffieHellman partB = DiffieHellman.newInstance(base);
                for (int j = 0; j < reset_c; j++) {
                    partA.resetPrivate();
                    partB.resetPrivate();
                    assertNotEquals(partA.getPublic(), partB.getPublic());
                    assertEquals(partA.shareSecretKey(partB.getPublic()), partB.shareSecretKey(partA.getPublic()));
                }
            }
            System.out.printf("bits %d, certainty %d, execute %d, duration %f s\n",
                    bits_a[inx], certainty_a[inx], ins_c * reset_c,
                    (float) (System.currentTimeMillis() - begin) / 1000);

        }
    }

}
