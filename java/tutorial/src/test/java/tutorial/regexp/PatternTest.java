package tutorial.regexp;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class PatternTest {
    
    @Test
    public void testIsTelphone(){

        String REGEX_TEL = "^(\\d{3,4}-)?\\d{6,8}$";
        Pattern PATTERN_REGEX_TEL = Pattern.compile(REGEX_TEL);
        
        assertTrue(PATTERN_REGEX_TEL.matcher("010-65727929").matches());
        assertFalse(PATTERN_REGEX_TEL.matcher("01065727929").matches());
    
    }

    @Test
    public void testWithQEQuoting(){

    }
}
