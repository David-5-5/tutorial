package tutorial.algo.leetcode;

import java.math.BigInteger;

public class Solution2514 {
    private static final int MOD = (int) 1e9 + 7;
    private static final BigInteger BIG_MOD = BigInteger.valueOf(MOD);
    private static final BigInteger EXPO = BigInteger.valueOf(MOD-2);

    public int countAnagrams(String s) {
        long ans = 1;
        String[] sub = s.split(" ");

        for (String cs : sub) {
            BigInteger a = new BigInteger("1"), b = new BigInteger("1");
            int[] cnt = new int[26];
            for (int i=0; i<cs.length(); i++) {
                a = a.multiply(new BigInteger(String.valueOf(i+1))).mod(BIG_MOD);
                int ch = cs.charAt(i) - 'a';
                cnt[ch]++;
                b = b.multiply(new BigInteger(String.valueOf(cnt[ch]))).mod(BIG_MOD);
            }
            ans = (ans * (a.multiply(b.modPow(EXPO, BIG_MOD))).mod(BIG_MOD).intValue()) % MOD;
        }

        return (int)ans;
    }
    
    // 快速幂
    private static long pow(long a, int e) {
        long res = 1, b = a;
        for (int i=0; i<31; i++) {
            if ((e >> i & 1 )== 1) {
                res = (res * b) % MOD;
            }
            b = (b * b) % MOD;
        }
        return res;
    }

    private static long pow2(long x, int n) {
        var res = 1L;
        for (; n > 0; n /= 2) {
            if (n % 2 > 0) res = res * x % MOD;
            x = x * x % MOD;
        }
        return res;
    } 

    public int countAnagrams2(String s) {
        long ans = 1;
        String[] sub = s.split(" ");
        // 中间变量 a, b 使用 long 类型，避免乘法溢出
        for (String cs : sub) {
            // 可以省略 a，直接乘以 ans
            long a = 1, b = 1;
            int[] cnt = new int[26];
            for (int i=0; i<cs.length(); i++) {
                a = (a * (i+1)) % MOD;
                int ch = cs.charAt(i) - 'a';
                cnt[ch]++;
                b = (b*cnt[ch]) % MOD;
            }
            ans = (ans * (a * pow(b, MOD-2)% MOD)) % MOD;
        }

        return (int)ans;
    }    

    public static void main(String[] args) {
        System.out.println(new Solution2514().countAnagrams2("b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp"));
        System.out.println(pow(344, MOD-2));
        System.out.println(pow2(344, MOD-2));
    }
}
