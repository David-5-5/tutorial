package tutorial;

import java.util.Random;

public class AddOverflow {
    public static void main( String[] args )
    {
        Random random = new Random();
        int start = 1000;
        for (int i=0; i<50000; i++) {
            start += Math.abs(random.nextInt());
            if (i % 1000 == 0)
                System.out.println(start);
        }
    }
}
