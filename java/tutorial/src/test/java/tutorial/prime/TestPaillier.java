package tutorial.prime;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.math.BigInteger;

import org.junit.jupiter.api.Test;

public class TestPaillier {

    @Test
    public void TestAdd() throws Exception {
        Paillier paillier = Paillier.newInstance(512, 50);

        BigInteger op1 = new BigInteger("2");
        BigInteger op2 = new BigInteger("8");

        assertEquals(new BigInteger("4"), op2.divide(op1));

        BigInteger c1 = paillier.enc(op1);
        assertEquals(op1, paillier.dec(c1));

        c1 = paillier.enc2(op1);
        assertEquals(op1, paillier.dec(c1));

        BigInteger c2 = paillier.enc(op2);
        assertEquals(op2, paillier.dec(c2));

        assertEquals(op1.add(op2), paillier.dec(c1.multiply(c2)));
    }
    
}
