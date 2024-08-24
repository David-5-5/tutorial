from typing import List

# 周赛 316
class Solution:
    def makeSimilar(self, nums: List[int], target: List[int]) -> int:
        # 参考题解
        ans = 0
        for i in range(2): # 自行解答，未按照模 2 分组
            sub_n = [v for v in nums if v % 2 == i]
            sub_t = [v for v in target if v % 2 == i]
            sub_n.sort()
            sub_t.sort()
            for u,v in zip(sub_n, sub_t):
                sub = u - v
                if sub > 0: ans += sub // 2

        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, target = [8,12,6], [2,14,10]
    print(sol.makeSimilar(nums, target))