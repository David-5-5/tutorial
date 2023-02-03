package tutorial.regexp;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class PatternTest {
    
    @Test
    public void testDigital(){
        Pattern regex1 = Pattern.compile("12");
        Pattern regex2 = Pattern.compile("^\\d{2,6}$");
        assertFalse(regex1.matcher("1").matches());
        assertFalse(regex2.matcher("2").matches());
        assertTrue(regex1.matcher("12").matches());
        assertTrue(regex2.matcher("21").matches());
        assertFalse(regex1.matcher("123456").matches());
        assertTrue(regex2.matcher("654321").matches());
        assertFalse(regex2.matcher("7654321").matches());

    }

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
