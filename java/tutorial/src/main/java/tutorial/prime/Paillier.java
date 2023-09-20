package tutorial.prime;

import static java.math.BigInteger.ONE;
import java.math.BigInteger;
import java.util.Random;

public class Paillier {
    static final int BITS = 256;
    static final int CERTAINTY = 20;

    // private key: (phi)
    // public key:  (n, g)
    private BigInteger n, g, phi;
    private BigInteger denominator;

    private Paillier(BigInteger p, BigInteger q) {
        this.n = p.multiply(q);
        this.g = n.add(ONE);
        this.phi = (p.subtract(ONE)).multiply(q.subtract(ONE));
    }    

    public static Paillier newInstance() {
        return newInstance(BITS, CERTAINTY);
    }

    public static Paillier newInstance(int bits, int certainty) {
        Random random = new Random();

        int adjustedBitLength = (int) Math.ceil(((double) bits) / 2);
        // p,q 为两个大质数
        BigInteger p = new BigInteger(adjustedBitLength, certainty, random);
        BigInteger q = new BigInteger(adjustedBitLength, certainty, random);
        while (q.compareTo(p) == 0) {
            q = new BigInteger(adjustedBitLength, certainty, random);
        }

        return new Paillier(p, q);
    }

    public BigInteger enc(BigInteger plain) {
        Random random = new Random();
        BigInteger r = new BigInteger(n.pow(2).bitLength(), random);

        // gcd(e, n^2) = 1, 即e, n^2 互质
        while (r.compareTo(ONE) <= 0 || !n.pow(2).gcd(r).equals(ONE) || r.compareTo(n.pow(2)) >= 0) {
            r = new BigInteger(n.pow(2).bitLength() - 1, random);
        }
        return r.modPow(n, n.pow(2)).multiply(plain.multiply(n).add(ONE)).mod(n.pow(2));
    }

    public BigInteger enc2(BigInteger plain) {
        Random random = new Random();
        BigInteger r = new BigInteger(n.pow(2).bitLength(), random);

        // gcd(e, n^2) = 1, 即e, n^2 互质
        while (r.compareTo(ONE) <= 0 || !n.pow(2).gcd(r).equals(ONE) || r.compareTo(n.pow(2)) >= 0) {
            r = new BigInteger(n.pow(2).bitLength() - 1, random);
        }
        return g.modPow(plain, n.pow(2)).multiply(r.modPow(n,n.pow(2))).mod(n.pow(2));
    }    

    public BigInteger dec(BigInteger chiper) {

        return chiper.modPow(phi, n.pow(2)).subtract(ONE).divide(n).add(n).divide(getDenominator());
    }

    public synchronized BigInteger getDenominator() {
        if (denominator == null) {
            denominator = g.modPow(phi, n.pow(2)).subtract(ONE).divide(n);
        }
        return denominator;
    }
}
