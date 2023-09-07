package tutorial.spec;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.fail;

import org.junit.jupiter.api.Test;

public class ExpressionTest {

    static final String message = "I'm outta here!";
    static int forgetIt() throws Exception {
        throw new Exception(message);
    }

    @Test
    public void testEvaluateLeftHandOperandFirst() {
        int i = 2;
        assertEquals(9, (i = 3) * i);

        i = 9;
        assertEquals(12, i += (i = 3));

        i = 9;
        assertEquals(12, i = i + (i = 3));

        i = 1;
        try {
            i = forgetIt() / (i = 2);
            fail();
        } catch (Exception e) {
            assertEquals(1, i);
        }
        try {
            i = (i = 2) / forgetIt() ;
            fail();
        } catch (Exception e) {
            assertEquals(2, i);
        }        
    }

    @Test
    public void testEvaluateOperandsBeforeOperation() {
        assertThrows(ArithmeticException.class, ()->{
            int i = 1 / 0 ;
            fail(String.valueOf(i));
        }, "/ by zero");


        assertThrows(Exception.class, ()->{
            int i = 1 /(0 * forgetIt());
            fail(String.valueOf(i));
        }, message);
    }

    @Test
    public strictfp void testEvaluateRespectsParenthesesPrecedence() {
        double d = 8e+307;
        assertEquals(2.0 * d, 1.6e+308);
        assertEquals(1.0 / 0.0, 4.0 * d * .5);
        assertEquals(Double.POSITIVE_INFINITY, 4.0 * d * .5);
        assertNotEquals(2.0 * d, 4.0 * d * .5);
    }
    
}
