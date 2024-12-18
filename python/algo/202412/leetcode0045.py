from typing import List

# 贪心专题 - 区间覆盖
class Solution:
    def jump(self, nums: List[int]) -> int:
        # 参考 1326 区间覆盖 模板
        n = len(nums)
        right_most = [0] * (n)
        for i, r in enumerate(nums):
            right_most[i] = max(right_most[i], i+r) # min(n-1, i+r)

        ans = 0
        cur_right = 0   # 当前右端点
        next_right = 0  # 当前右端点覆盖的后续区间的右端点最大值
        for i in range(n-1):  
            # if cur_right >= n-1 : break # 可以不用
            next_right = max(next_right, right_most[i])
            if i == cur_right:  # 到达已建造的桥的右端点
                cur_right = next_right  # 造一座桥
                ans += 1

        return ans
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.jump([2,3,1,1,4]))
