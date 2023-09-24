package tutorial.privacycomputing;

import static java.math.BigInteger.ONE;

import java.math.BigInteger;
import java.security.SecureRandom;

public class Paillier implements PrimeGeneratable {


    // private key: (phi)
    // public key:  (n, g)
    private BigInteger n, g, phi, nSquare;
    private BigInteger denominator;

    private Paillier(BigInteger p, BigInteger q) {
        this.n = p.multiply(q);
        this.g = n.add(ONE);
        this.phi = (p.subtract(ONE)).multiply(q.subtract(ONE));
        this.nSquare = n.multiply(n);
    }    

    public static Paillier newInstance() {
        return newInstance(BITS, CERTAINTY);
    }

    public static Paillier newInstance(int bits, int certainty) {
        SecureRandom random = new SecureRandom();

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
        SecureRandom random = new SecureRandom();
        BigInteger r = new BigInteger(nSquare.bitLength(), random);

        // gcd(e, n^2) = 1, 即e, n^2 互质
        while (r.compareTo(ONE) <= 0 || !nSquare.gcd(r).equals(ONE) || r.compareTo(nSquare) >= 0) {
            r = new BigInteger(nSquare.bitLength() - 1, random);
        }
        return r.modPow(n, nSquare).multiply(plain.multiply(n).add(ONE)).mod(nSquare);
    }

    public BigInteger enc2(BigInteger plain) {
        SecureRandom random = new SecureRandom();
        BigInteger r = new BigInteger(nSquare.bitLength(), random);

        // gcd(e, n^2) = 1, 即e, n^2 互质
        while (r.compareTo(ONE) <= 0 || !nSquare.gcd(r).equals(ONE) || r.compareTo(nSquare) >= 0) {
            r = new BigInteger(nSquare.bitLength() - 1, random);
        }
        return g.modPow(plain, nSquare).multiply(r.modPow(n, nSquare)).mod(nSquare);
    }    

    public BigInteger dec(BigInteger chiper) {

        return chiper.modPow(phi, nSquare).subtract(ONE).divide(n).multiply(getDenominator().modInverse(n)).mod(n);
    }

    // The value is equals to phi
    // It should depend on g, where g = n + 1, the result is equals to phi
    private synchronized BigInteger getDenominator() {
        if (denominator == null) {
            denominator = g.modPow(phi, nSquare).subtract(ONE).divide(n);
        }
        return denominator;
    }

    public BigInteger getNSquare() {
        return nSquare;
    }
}
