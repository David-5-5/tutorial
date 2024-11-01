from itertools import permutations
from typing import List

# 专题: 全排列
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        # 全排列 模板
        n = len(nums)
        
        ans = []
        path = [0] * n
        def dfs(i, s):
            if i == n:
                ans.append(path.copy())
                return
            
            for x in s:
                path[i] = x 
                dfs(i+1, s-{x})
                # path长度固定，覆盖以前数据，无需恢复现场

        dfs(0, set(nums))
        return ans

    def permute2(self, nums: List[int]) -> List[List[int]]:
        # 全排列 模板 另一种写法
        n = len(nums)
        
        ans = []
        path = []
        def dfs(i, s):
            if i == n:
                ans.append(path.copy())
                return
            l = len(path)
            for x in s:
                path.append(x)
                dfs(i+1, s-{x})
                del path[l]   # 恢复现场

        dfs(0, set(nums))
        return ans

    def permute3(self, nums: List[int]) -> List[List[int]]:
        # 系统函数
        return list(permutations(nums))

if __name__ == "__main__":
    sol = Solution()
    nums = [1,2,3]
    print(sol.permute3(nums))