package tutorial.algo.leetcode;

// 双周赛 125
public class Solution3068 {
    // 参考题解
    // 状态转移方程 数组仅偶数个数进行异或操作
    // f[i+1][0] = max(f[i][0] + x, f[i][1] + x ^ k)
    // f[i+1][1] = max(f[i][1] + x, f[i][0] + x ^ k)
    // f[0][0] = 0 f[0][1] = -inf
    public long maximumValueSum(int[] nums, int k, int[][] edges) {
        long f0 = 0, f1 = Long.MIN_VALUE;
        long t;
        
        for (int num : nums) {
            t = Math.max(f1 + num, f0 + num ^ k);
            f0 = Math.max(f0 + num, f1 + num ^ k);
            f1 = t;
        }   
        return f0;
    }
    
}
