package tutorial.algo.leetcode;

import java.util.PriorityQueue;

// 双周赛 125
public class Solution3066 {

    public int minOperations(int[] nums, int k) {
        PriorityQueue<Long> numbers = new PriorityQueue<>();
        for (int x :nums)
            numbers.add((long)x);
        
        int ans = 0;
        while (numbers.size() > 1 && numbers.peek() < k)  {
            long a = numbers.poll();
            long b = numbers.poll();
            numbers.add((a*2 + b));
            ans ++;
        }
        return ans;
    }

    public static void main(String[] args ) {
        int[] nums = new int[]{1000000000,999999999,1000000000,999999999,1000000000,999999999};
        System.out.println(new Solution3066().minOperations(nums, 1000000000));

    }
}
