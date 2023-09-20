package tutorial.prime;

import static java.math.BigInteger.ONE;

import java.math.BigInteger;
import java.util.Random;

public class SimpleRSA {
    static final int BITS = 256;
    static final int CERTAINTY = 20;

    // private key: (n, d)
    // public key:  (n, e)
    private BigInteger n, e, d;

    private SimpleRSA(BigInteger p, BigInteger q, BigInteger e, BigInteger d) {

        this.e = e;
        this.d = d;
        this.n = p.multiply(q);
    }

    public static SimpleRSA newInstance() {
        return newInstance(BITS, CERTAINTY);
    }

    public static SimpleRSA newInstance(int bits, int certainty) {
        Random r = new Random();

        int adjustedBitLength = (int) Math.ceil(((double) bits) / 2);
        // p,q 为两个大质数
        BigInteger p = new BigInteger(adjustedBitLength, certainty, r);
        BigInteger q = new BigInteger(adjustedBitLength, certainty, r);
        while (q.compareTo(p) == 0) {
            q = new BigInteger(adjustedBitLength, certainty, r);
        }
        BigInteger phi = (p.subtract(ONE)).multiply(q.subtract(ONE));
        BigInteger e = new BigInteger(phi.bitLength(), r);

        // gcd(e, phi) = 1, 即e, phi 互质
        while (e.compareTo(ONE) <= 0 || !phi.gcd(e).equals(ONE) || e.compareTo(phi) >= 0) {
            e = new BigInteger(phi.bitLength() - 1, r);
        }
        // 求 e 对于模phi的逆元, 从n需要np的时间计算出p, q, 才能计算出phi, 以便进一步计算出
        // 私钥中的 e 的逆元 d 
        BigInteger d = e.modInverse(phi);
        return new SimpleRSA(p, q, e, d);
    }

    public BigInteger enc(BigInteger plain) {
        return plain.modPow(e, n);
    }

    public BigInteger dec(BigInteger cipher) {
        return cipher.modPow(d, n);
    }

}
