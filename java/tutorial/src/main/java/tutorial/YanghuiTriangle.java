package tutorial;

import java.util.Scanner;

public class YanghuiTriangle {

    public static void main(String[] args) {
        try (Scanner scan = new Scanner(System.in)) {
            int n = scan.nextInt() - 1;

            System.out.println((int)Math.pow(2, Integer.bitCount(n)));
        }
    }


}