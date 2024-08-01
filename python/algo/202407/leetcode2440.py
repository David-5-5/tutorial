from typing import List


class Solution:
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        g = [[] for _ in range(n)]

        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        def dfs(u:int, fa:int) -> int:
            su = nums[u]
            for v in g[u]:
                if v == fa:continue
                sc = dfs(v, u)
                if sc == -1: return -1
                su += sc
            if su == target:
                return 0
            elif su > target:
                return -1
            return su

        total = sum(nums)
        for i in range(n, 0, -1):
            if total % i == 0:
                target = total // i
                if dfs(0, -1) == 0:return i - 1
        

if __name__ == "__main__":
    sol = Solution()
    nums, edges = [6,2,2,2,6], [[0,1],[1,2],[1,3],[3,4]] 
    print(sol.componentValue(nums, edges))