package tutorial.algo.acmcoder.acm03;

import java.util.HashMap;
import java.util.Scanner;

public class Main {
    static int tempMod = 1000000007;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String bd = in.nextLine();
        int n = in.nextInt();
        int[] nums = new int[n];

        for (int i = 0; i < n; i++) {
            nums[i] = in.nextInt();
        }
        for (int i=0;i<n;i++) {
            System.out.println(find(bd, nums[i]));
        }
    }

    public static int find(String bd, int remainder) {
        int count = 0;
        for (int i=0;i<=bd.length()-1;i++) {
            long remin = bd.charAt(i) - '0';
            if (remin == remainder) {
                count ++;
                if (i>0) {
                    for (int k = i-1;k>=0;k--) {
                        if (bd.charAt(k)=='0') count++;
                        else break;
                    }
                }
            }
            if (remin !=0) {
                for (int j = i+1;j<bd.length();j++) {
                    remin = (remin * 10) % tempMod+ (bd.charAt(j)-'0') % tempMod;
                    if (remin == remainder) {
                        count ++;
                        if (i>0) {
                            for (int k = i-1;k>=0;k--) {
                                if (bd.charAt(k)=='0') count++;
                                else break;
                            }
                        }
                    }

                }
            }
        }

        return count;
    }
    public static int find2(String bd, int target) {
        int count = 0;
        HashMap<Integer, Integer> cur = new HashMap<>();
        HashMap<Integer, Integer> next = new HashMap<>();

        for (int i=0;i<bd.length();i++) {
            int d = bd.charAt(i) - '0';
            for (Integer key : cur.keySet()) {
                Integer newkey = (key * 10 + d) % tempMod;
                Integer oldvalue = next.getOrDefault(newkey, 0);
                next.put(newkey, oldvalue+cur.get(key));
            }
            next.put(d, 1+next.getOrDefault(d, 0));

            count += next.getOrDefault(target, 0);
            cur = next;
            next = new HashMap<>();
        }

        return count;
    }    
}
