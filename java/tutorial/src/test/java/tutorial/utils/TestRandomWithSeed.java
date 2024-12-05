package tutorial.utils;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import java.util.Random;

import org.junit.jupiter.api.Test;

/*
 * <p>Random number generation plays a crucial role in modern computing. 
 * They are used in a variety of applications, from simple games and 
 * simulations to complex cryptographic and financial models. However, 
 * in some cases, we want to ensure that random number generation is 
 * consistent and reproducible. This is where random seed comes into play.<p>
 * 
 * <p>In contrast to disordered randomness, random seeds provide a way to
 * control the “randomness” of a random number generator so that it can
 * reproduce the same random sequence in a deterministic way. In contrast
 * to the physically random process of flipping a coin or rolling a die,
 * random seeds allow us to accurately replicate these processes in a virtual
 * environment, as if there were a virtual coin or die that gives the same
 * result every time it is flipped.Translated with DeepL.com (free version) </p>
 * 
 */
public class TestRandomWithSeed {

    @Test
    public void TestGenerateIntWithSameSeed() {
        Random random = new Random(123456);

        Integer rds[] = new Integer[10];
        for (int i = 0; i < rds.length; i++) {
            rds[i] = random.nextInt();
        }

        random = new Random(123456);

        Integer rds2[] = new Integer[10];
        for (int i = 0; i < rds2.length; i++) {
            rds2[i] = random.nextInt();
        }

        assertTrue(Arrays.deepEquals(rds, rds2));

    }

    @Test
    public void TestGenerateDoubleWithSameSeed() {
        Random random = new Random(123456);

        Double rds[] = new Double[10];
        for (int i = 0; i < rds.length; i++) {
            rds[i] = random.nextDouble();
        }

        random = new Random(123456);

        Double rds2[] = new Double[10];
        for (int i = 0; i < rds2.length; i++) {
            rds2[i] = random.nextDouble();
        }

        assertTrue(Arrays.deepEquals(rds, rds2));

    }

    @Test
    public void TestGenerateHybridTypeWithSameSeed() {
        Random random = new Random(123456);

        Object rds[] = new Object[10];
        for (int i = 0; i < rds.length; i++) {
            rds[i] = random.nextDouble();
            rds[++i] = random.nextInt();
        }

        // Reset the seed replace of instantiatation
        random.setSeed(123456);
        ;

        Object rds2[] = new Object[10];
        for (int i = 0; i < rds2.length; i++) { // Each loop i += 2
            rds2[i] = random.nextDouble();
            rds2[++i] = random.nextInt();
        }

        assertTrue(Arrays.deepEquals(rds, rds2));

    }

    @Test
    public void TestGenerateDoubleWithDifferentSeed() {
        Random random = new Random(123456);

        Double rds[] = new Double[10];
        for (int i = 0; i < rds.length; i++) {
            rds[i] = random.nextDouble();
        }

        random = new Random(234561);

        Double rds2[] = new Double[10];
        for (int i = 0; i < rds2.length; i++) {
            rds2[i] = random.nextDouble();
        }

        assertFalse(Arrays.deepEquals(rds, rds2));

    }
}