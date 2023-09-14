package tutorial.spec;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.fail;

import org.junit.jupiter.api.Test;

public class ExpressionTest {

    static final String message = "I'm outta here!";

    static int forgetIt() throws Exception {
        throw new Exception(message);
    }

    static String concate(String s1, String s2) {
        return s1 + s2;
    }

    static int sum(int a, int b, int c) {
        return a + b + c;
    }

    static int oops() throws Exception {
        throw new Exception("oops");
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
            i = (i = 2) / forgetIt();
            fail();
        } catch (Exception e) {
            assertEquals(2, i);
        }
    }

    @Test
    public void testEvaluateOperandsBeforeOperation() {
        assertThrows(ArithmeticException.class, () -> {
            int i = 1 / 0;
            fail(String.valueOf(i));
        }, "/ by zero");

        assertThrows(Exception.class, () -> {
            int i = 1 / (0 * forgetIt());
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

    @Test
    public void testEvaluateLeftToRight() {
        String s = "going, ";
        assertEquals("going, gone", concate(s, s = "gone"));
        int id = 0;
        try {
            sum(id = 1, oops(), id = 3);
        } catch (Exception e) {
            assertEquals(1, id);
        }
    }

    static class List {
        int value;
        List next;
        static List head = new List(0);

        List(int n) {
            value = n;
            next = head;
            head = this;
        }
    }

    @Test
    /**
     * Because it will tigger OutOfMemeory error, it would execute for a
     * considerable amount of time
     * 
     * For vscode should set the -Xmx for vmAgs to limit the duration.
     * In .vscode/settings.json file, add as following for example:
     * "java.test.config": {
     * "vmArgs": ["-Xmx64M"]
     * },
     * In maven, add configuration in pom.xml as following:
     * <plugin>
     * <artifactId>maven-surefire-plugin</artifactId>
     * <version>2.22.1</version>
     * <configuration>
     * <argLine>-Xmx64M</argLine>
     * <includes>
     * <include>ExpressionTest.java</include>
     * </includes>
     * </configuration>
     * </plugin>
     */
    public void testEvaluateOrderAndOutOfMemoryDetection() {
        int id = 0, oldid = 0;
        try {
            for (;;) {
                ++id;
                new List(oldid = id);
            }
        } catch (Error e) {
            List.head = null;
            assertFalse(oldid == id);
        }
    }

    @Test
    public void testMethodReference() {
        C c = new C();
        assertEquals(0, c.test());
    }
}

@FunctionalInterface
interface Fun<T, R> {
    R apply(T arg);
}

class C {
    // int size() {
    //     return 0;
    // }

    static int size(Object arg) {
        return 0;
    }

    int test() {
        Fun<C, Integer> f1 = C::size;
        // Error: instance method size()
        // or static method size(Object)?
        return f1.apply(this);
    }
}