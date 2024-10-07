from typing import List

# 周赛 349
class Solution:
    def minCost(self, nums: List[int], x: int) -> int:
        # 参考题解

        # 1, 不操作 总成本是多少？ sum(nums)
        # 2, 最多操作多少次? 最多操作 n-1 次
        # 3, 操作一次的总成本 -> 连续子数组最小值
        # 预处理 连续子数组的最小值
        ans, n = sum(nums), len(nums)
        
        # mx[i][j] 表示 i 表示 连续子数组长度(不包括第一个数组)
        # mx[i][j] = min(nums[j:j+i+1])
        # mx = [[0] * n for _ in range(n)]
        # mx[0] = nums
        # for i in range(1, n):
        #     for j in range(n):
        #         mx[i][j] = min(mx[i-1][j], nums[(j+i)%n])
        #     ans = min(ans, sum(mx[i]) + x*i)

        # 优化空间
        mx_prev, mx_cur = nums, [0] * n
        for i in range(1, n):
            for j in range(n):
                mx_cur[j] = min(mx_prev[j], nums[(j+i)%n])
            ans = min(ans, sum(mx_cur) + x*i)
            # if sum(mx_cur) + x*i < ans: ans = sum(mx_cur) + x*i
            mx_prev, mx_cur = mx_cur, [0] * n
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, x = [20,1,15], 5
    print(sol.minCost(nums, x))