package tutorial.algo.leetcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// Java 前缀和
// int to long 显式转换
public class Solution2602 {
    public List<Long> minOperations(int[] nums, int[] queries) {
        int n = nums.length;
        Arrays.sort(nums);

        long[] preSum = new long[n+1];
        for (int i=1; i<=n; i++) {
            preSum[i] = nums[i-1] + preSum[i-1];
        }
        
        List<Long> ans = new ArrayList<>();
        for (int q:queries) {
            Long res = 0l;
            // int inx = Arrays.binarySearch(nums, q);
            // if (inx < 0) inx = -inx - 1;

            // using customer method instead of Array.binarySearch
            int inx = lowerBound(nums, q);
            res += ((long)q * inx) - (preSum[inx] - preSum[0]);
            res += (preSum[n]- preSum[inx]) - ((long)q * (n-inx));
            ans.add(res);
        }

        return ans;
    }

    private int lowerBound(int[] nums, int target) {
        int left = -1;
        int right = nums.length; // 开区间 (left, right)
        while (left + 1 < right) { // 区间不为空
            // 循环不变量：
            // nums[left] < target
            // nums[right] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid; // 范围缩小到 (mid, right)
            } else {
                right = mid; // 范围缩小到 (left, mid)
            }
        }
        return right;
    }

    public static void main(String[] args) {
        int[] nums = new int[]{3,1,6,8}, queries= new int[]{1,5};
        System.out.println(new Solution2602().minOperations(nums, queries));
    }
}
