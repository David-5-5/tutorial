from cmath import inf
from functools import reduce
from operator import xor
from typing import List

# 周赛 299 
class Solution:
    def minimumScore(self, nums: List[int], edges: List[List[int]]) -> int:
        # 参考题解
        n = len(nums)

        xor_s = reduce(xor, nums)

        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        cuts = [] # 删除边的的子结点
        timestamp = [[0,0] for _ in range(n)] # (in, out)
        xors = [0] * n # 以个节点的
        
        time = 1
        def dfs(u:int, fa:int) -> int:
            nonlocal time
            # set timestamp of in
            timestamp[u][0] = time
            time += 1
            xor_cur = nums[u]
            for v in g[u]:
                if v == fa:continue
                cuts.append(v)
                xor_cur ^= dfs(v, u)
            
            # set timestamp of in
            timestamp[u][1] = time
            time += 1
            xors[u] = xor_cur
            return xor_cur

        def is_ancestor(u:int, v:int) -> bool:
            if timestamp[u][0] < timestamp[v][0] and timestamp[u][1] > timestamp[v][1]:
                return True
            else: return False

        dfs(1, -1)
        ans = inf
        for i in range(n-2):
            for j in range(i+1, n-1):
                u, v = cuts[i], cuts[j]
                # u is ancetor of v or v is ancetor of u
                xor1 = xor2 = xor3 = 0
                if is_ancestor(u, v):
                    xor1,xor2 = xors[u] ^ xors[v], xors[v]
                elif is_ancestor(v, u):
                    xor1,xor2 = xors[u] ^ xors[v], xors[u]
                else:
                    xor1,xor2 = xors[u], xors[v]
                xor3 = xor_s ^ xor1 ^ xor2
                
                ans = min(ans, max(xor1,xor2,xor3)-min(xor1,xor2,xor3))

        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, edges = [1,5,5,4,11], [[0,1],[1,2],[1,3],[3,4]]
    nums, edges = [5,5,2,4,4,2], [[0,1],[1,2],[5,2],[4,3],[1,3]]
    print(sol.minimumScore(nums, edges))

