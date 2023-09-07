package tutorial.spec;

import static org.hamcrest.core.Is.is;
import static org.junit.Assert.assertThat;

import org.junit.Test;
public class CalculatorTest {
    @Test
    public void testSumWithStrcitFP() {

        double result = Calculator.sumWithfp(23e10, 98e17);
        assertThat(result, is(9.800000230000001E18));
    
        result = Calculator.diffWithfp(Double.MAX_VALUE, 1.56);
        assertThat(result, is(1.7976931348623157E308));

        assertThat(Calculator.sum(0.1, 0.2), is(0.30000000000000004));
    }

    @Test
    public void testSum() {

        double result = Calculator.sum(23e10, 98e17);
        assertThat(result, is(9.800000230000001E18));
    
        result = Calculator.diff(Double.MAX_VALUE, 1.56);
        assertThat(result, is(1.7976931348623157E308));

        assertThat(Calculator.sum(0.1, 0.2), is(0.30000000000000004));
    }
}
