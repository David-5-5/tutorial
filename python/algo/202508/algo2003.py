from typing import List

# 一般树 - 3.10 树上启发式合并
class Solution:
    def smallestMissingValueSubtree(self, parents: List[int], nums: List[int]) -> List[int]:
        # 自行解答 从 C++ 翻译而来
        n = len(parents)
        g = [[] for _ in range(n)]
        for i in range(1, n):
            g[parents[i]].append(i)

        ans = [1] * n

        def dfs(u:int ) -> set[list]:
            cur = set()
            cur.add(nums[u])

            # 下面代码中注释的语句，避免了 ans[u] 的线性增加
            for v in g[u]:
                child = dfs(v)
                ans[u] = max(ans[v], ans[u])    # 取子节点的最大值
                if len(child) > len(cur): cur, child = child, cur
                cur |= child
            
            while ans[u] in cur: ans[u] += 1    # 继续增大直至不在 cur 中
            return cur
        
        dfs(0)
        return ans
