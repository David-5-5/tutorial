package tutorial.algo;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        // int m = in.nextInt();
        
        // PriorityQueue<int[]> pq = new PriorityQueue<>();
        // HashMap<Integer, Integer> ct = new HashMap<>();
        // ArrayList<Integer> occpied = new ArrayList<>();

        // pq.offer(new int[]{n*2, 1, n,});
        int[] nums = new int[n];
        for (int i=0; i<n;i++) {
            nums[i] = in.nextInt();
        }

        int[] f = new int[n+1];
        f[0] = 1;

        for (int i = 1; i<=n; i++) {
            int[] col = new int[10];
            for (int j=i; j>0; j--) {
                col[nums[j-1]] += 1;
                if (col[nums[j-1]] > 1) break;
                f[i] = f[i] + f[j-1];
            }
        }

        System.out.println(f[n]);

    }
}
