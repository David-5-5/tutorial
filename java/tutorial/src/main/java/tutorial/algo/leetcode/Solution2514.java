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

    public static void main(String[] args) {
        System.out.println(new Solution2514().countAnagrams("b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp"));
    }
}
