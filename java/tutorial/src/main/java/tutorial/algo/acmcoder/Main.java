package tutorial.algo.acmcoder;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int ans = 0;
        try (Scanner in = new Scanner(System.in)) {
            int n = in.nextInt();
            int k = in.nextInt();
            int[] nums = new int[n];

            for (int i = 0; i < n; i++) {
                nums[i] = in.nextInt();
            }

            int l = 0, zero = 0;

            for (int r = 0; r<n; r++) {
                if (nums[r] == 0) zero+=1;

                while (zero > k) {
                    if (nums[l] == 0) zero --;
                    l ++;
                }
                ans = Math.max(ans, r-l +1);
            }   
        } finally {
            System.out.print(ans);
        }
    }
}
