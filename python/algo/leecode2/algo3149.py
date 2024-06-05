from typing import List
from functools import lru_cache
# 按照题意，是score计算的公式组成一个闭环的链，因此可以固定从0开始遍历。（字典序最小）
# 例如 score(3 -> 1 -> 0 -> 4 -> 2) = score(1 -> 0 -> 4 -> 2 -> 3) = score(0 -> 4 -> 2 -> 3 -> 1)
# dfs 求出最小值
# print_ans 与 dfs 的结构一致，打印出最终结果，套路
class Solution:
    def findPermutation(self, nums: List[int]) -> List[int]:
        n = len(nums)

        @lru_cache(maxsize = None)
        def dfs(s, p)->int:
            if s == (1<<n) - 1:
                return abs(p-nums[0]) 
            
            res = float("inf")
            for i in range(n):
                if s >> i & 1 == 1:
                    continue
                res = min(res, dfs(s | (1<<i), i) + abs(p-nums[i]))
            return res

        # dfs(1,0)
        # return dfs(1,0)

        ans = []
        def print_ans(s,p):
            ans.append(p)
            if s == (1<<n) - 1:
                return abs(p-nums[0]) 
            
            final_res = dfs(s,p)
            for i in range(n):
                if s >> i & 1 == 1:
                    continue
                if dfs(s | (1<<i), i) + abs(p-nums[i]) == final_res:
                    print_ans(s | (1<<i), i)
                    break
        print_ans(1,0)
        return ans
                    

if __name__ == "__main__":
    sol = Solution()
    nums =  [0,1,2]
    print(sol.findPermutation(nums))