package tutorial.spec;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class CalculatorTest {
    @Test
    public void testSumWithStrcitFP() {

        assertEquals(Calculator.sumWithfp(23e10, 98e17), 9.800000230000001E18);
    
        assertEquals(Calculator.diffWithfp(Double.MAX_VALUE, 1.56), 1.7976931348623157E308);

        assertEquals(Calculator.sum(0.1, 0.2), 0.30000000000000004);
    }

    @Test
    public void testSum() {

        assertEquals(Calculator.sum(23e10, 98e17), 9.800000230000001E18);
    
        assertEquals(Calculator.diff(Double.MAX_VALUE, 1.56), 1.7976931348623157E308);

        assertEquals(Calculator.sum(0.1, 0.2), 0.30000000000000004);
    }
}
