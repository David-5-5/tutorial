package tutorial.privacycomputing;

import java.math.BigInteger;
import java.security.SecureRandom;

import lombok.Data;

public class DiffieHellman implements PrimeGeneratable {
    BaseDiffieHellman base;
    BigInteger pri;

    private DiffieHellman(BaseDiffieHellman base, BigInteger random) {
        this.base = base;
        this.pri = random;
    }

    public static DiffieHellman newInstance(BaseDiffieHellman base) {
        SecureRandom r = new SecureRandom();

        int adjustedBitLength = (int) Math.ceil(((double) base.getBits()) / 2);
        // p,q 为两个大质数
        BigInteger pri = new BigInteger(adjustedBitLength, base.getCertainty(), r);
        return new DiffieHellman(base, pri);
    }

    public void resetPrivate() {
        SecureRandom r = new SecureRandom();
        int adjustedBitLength = (int) Math.ceil(((double) base.getBits()) / 2);
        pri = new BigInteger(adjustedBitLength, base.getCertainty(), r);
    }

    public BigInteger getPublic() {
        return base.getG().modPow(pri, base.getP());
    }

    public BigInteger shareSecretKey(BigInteger otherPub) {
        return otherPub.modPow(pri, base.getP());
    }

}

@Data
class BaseDiffieHellman implements PrimeGeneratable {
    private int bits, certainty;
    private BigInteger p, g;

    private BaseDiffieHellman(int bits, int certainty, BigInteger p, BigInteger g) {
        this.bits = bits;
        this.certainty = certainty;
        this.p = p;
        this.g = g;
    }

    public static BaseDiffieHellman newInstance() {
        return newInstance(BITS, CERTAINTY);
    }    

    public static BaseDiffieHellman newInstance(int bits, int certainty) {
        SecureRandom r = new SecureRandom();

        int adjustedBitLength = (int) Math.ceil(((double) bits) / 2);
        // p,q 为两个大质数
        BigInteger p = new BigInteger(adjustedBitLength, certainty, r);
        
        // TODO: g should be prime root
        BigInteger g = new BigInteger((int) Math.ceil(adjustedBitLength / 2), certainty, r);

        return new BaseDiffieHellman(bits, certainty, p, g);
    }

}
