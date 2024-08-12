from typing import Counter, List

# 周赛 321 
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        # 参考题解
        # k 为中位数，则 cnt_less (+1 where even) == cnt_great
        # 由于 nums 未排序，因此 cnt_less_left + cnt_less_right = cnt_great_left + cnt_great_right
        #                     cnt_less_left - cnt_great_left = cnt_great_right - cnt_less_left
        pos = nums.index(k)
        cnt = Counter()

        val,cnt[0] = 0, 1 # cnt[0] = 1 k 本身就是中位数
        for i in range(pos+1, len(nums)):
            if nums[i] > k:
                val += 1
            else: val -= 1
            cnt[val] += 1
        
        ans = cnt[0] + cnt[1] # k 仅和右边中位数数量
        val = 0

        for i in range(pos-1, -1, -1):
            if nums[i] < k:
                val += 1
            else: val -=1
            ans += cnt[val] + cnt[val+1]

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [3,2,1,4,5], 4
    print(sol.countSubarrays(nums, k))