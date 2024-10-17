package tutorial.algo.leetcode;

public class Solution0010 {
    public boolean isMatch(String s, String p) {
        int n = s.length(), m = p.length();

        boolean[][] dp = new boolean[n + 1][m + 1];
        dp[0][0] = true;
        // 边界值 p = "a*b*c*" 可以 匹配 “”
        for (int i = 1; i < m; i+=2) {
            if (p.charAt(i) == '*') dp[0][i+1] = dp[0][i-1];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (p.charAt(j) == '*') {
                    dp[i + 1][j + 1] = dp[i + 1][j] | dp[i + 1][j - 1]
                            | dp[i][j+1] & (p.charAt(j - 1) == '.' | p.charAt(j - 1) == s.charAt(i));
                } else if (p.charAt(j) == '.') {
                    dp[i + 1][j + 1] = dp[i][j];
                } else
                    dp[i + 1][j + 1] = dp[i][j] & s.charAt(i) == p.charAt(j);

            }

        }

        return dp[n][m];
        
    }
}
