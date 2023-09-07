package tutorial.regexp;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class PatternTest {
    
    @Test
    public void testDigital(){
        Pattern regex1 = Pattern.compile("\\d{2,6}?");
        Pattern regex2 = Pattern.compile("^\\d{3,4}$");

        assertFalse(regex1.matcher("1").matches());
        assertFalse(regex2.matcher("2").matches());

        assertTrue(regex1.matcher("12").matches());
        assertTrue(regex2.matcher("021").matches());

        // assertTrue(regex1.matcher("12333333").matches());
        assertFalse(regex2.matcher("a21").matches());

        // assertTrue(regex1.matcher("12b").matches());
        assertFalse(regex2.matcher("21b").matches());

        // assertTrue(regex1.matcher("a12b").matches());
        assertFalse(regex2.matcher("a1b").matches());


        assertTrue(regex1.matcher("123456").matches());
        //assertTrue(regex2.matcher("654321").matches());
        assertFalse(regex2.matcher("7654321").matches());

    }

    @Test
    public void testSameWithBeginAndEnd(){
        Pattern regex1 = Pattern.compile("([a-z]).*\\1");
        Pattern regex2 = Pattern.compile("^[a-z]$|^([a-z]).*\\1$");
        assertTrue(regex1.matcher("ab1ca").matches());
        assertTrue(regex2.matcher("ab1ca").matches());
    }

    @Test
    public void testIsTelphone(){

        String REGEX_TEL = "^(\\d{3,4}-)?\\d{6,8}$";
        Pattern PATTERN_REGEX_TEL = Pattern.compile(REGEX_TEL);
        
        assertTrue(PATTERN_REGEX_TEL.matcher("010-65727929").matches());
        assertFalse(PATTERN_REGEX_TEL.matcher("01065727929").matches());
    
    }

    @Test
    public void testIsTelphoneWithoutBeginAndEnd(){

        String REGEX_TEL = "(\\d{3,4}-)?\\d{6,8}";
        Pattern PATTERN_REGEX_TEL = Pattern.compile(REGEX_TEL);
        
        assertTrue(PATTERN_REGEX_TEL.matcher("010-65727929").matches());
        assertFalse(PATTERN_REGEX_TEL.matcher("01065727929").matches());
    
    }

    @Test
    public void testWithQEQuoting(){
        
    }

}
