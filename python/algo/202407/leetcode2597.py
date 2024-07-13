from collections import Counter, defaultdict
from functools import cache
from typing import List


class Solution:
    # 方法一 子集型回溯, 时间复杂度 O(2^n)
    def beautifulSubsets(self, nums: List[int], k: int) -> int:
        ans = -1
        n = len(nums)
        d = defaultdict(int)
        def dfs(i:int) -> int:
            nonlocal ans
            if i == n:
                ans += 1
                return 
            
            # not select
            dfs(i+1)

            # select
            if d[nums[i]-k]==0 and d[nums[i]-k]==0:
                d[nums[i]] += 1
                dfs(i+1)
                d[nums[i]] -= 1
        
        dfs(0)
        return ans

    # 方法二 动态规划, 时间复杂度 O(2^n)
    # 乘法原理，nums[i] % k 之间不同余，则不同的余之间不可能相差 k ，
    # 因此不同余之间的数量使用乘法原理相乘
    # 同余的数之间排序，并计算每个数出现的次数，使用Counter, 
    # 只用同余相邻的两个数之间的差 可能 等于 k
    # 动态规划，某个同余的不同的数有 m 个，最后一个数出现的次数为 x
    #   - 若不选，从 m-1 个数开始选择，
    #   - 若选，选择的方案 2^x -1 (1为不选的方案)，若 第m个数和m-1个数相差 k，则转移到 m-2 个数，否则转移到 m-1个数
    # 状态转移方程为：
    # dp[m-1] = dp[m-2] + 2^x -1 * (dp[m-2], g[m-1] - g[m-2] != k
    #                               dp[m-3], g[m-1] - g[m-2] == k)
    def beautifulSubsets2(self, nums: List[int], k: int) -> int:
        # 按余数分组
        rem = defaultdict(Counter)
        for num in nums:
            rem[num % k][num] += 1

        ans = 1

        for cv in rem.values():
            g = sorted([[k, v] for k, v in cv.items()], key=lambda p:p[0])
            n = len(g)
            @cache
            def dfs(i:int):
                if i < 0:
                    return 1

                # 不选
                res = dfs(i-1)
                res += (2 ** g[i][1] - 1 ) * (dfs(i-1) if i == 0 or g[i][0]-g[i-1][0] != k else dfs(i-2))
                return res
            ans *= dfs(n-1)
        return ans - 1


if __name__ == "__main__":
    sol = Solution()
    nums, k = [2,4,6], 2
    print(sol.beautifulSubsets(nums, k))
    print(sol.beautifulSubsets2(nums, k))