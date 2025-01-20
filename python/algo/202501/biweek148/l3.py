from math import inf
from typing import List

# 3425
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        # dfs 参考题解，数据结构综合技巧
        g = [[] for _ in nums]
        for u, v, l in edges:
            g[u].append((v, l))
            g[v].append((u, l))

        ans = (-1, 0)
        depths = {}
        dis = [0] # 从根节点开始遍历，路径长度，类似前缀和
        def dfs(u:int, fa:int, top_depth) -> tuple[int, int]:
            color = nums[u]
            old_depth = depths.get(color, 0)
            
            # top_depth 不包含重复元素的最远节点
            # 随着重复元素的发现，top_depth 逐渐增加
            top_depth = max(old_depth, top_depth) 
            nonlocal ans
            ans = max(ans, (dis[-1]-dis[top_depth], top_depth - len(dis)))
            
            depths[color] = len(dis)
            for v, l in g[u]:
                if v == fa: continue
                dis.append(l + dis[-1])

                dfs(v, u, top_depth)
                dis.pop()  # 恢复现场
            depths[color] = old_depth
        
        dfs(0,-1,0)
        return [ans[0], -ans[1]]

            
if __name__ == "__main__":
    sol = Solution()
    edges = [[1,0,7],[1,2,4]]
    nums = [1,1,3]
    print(sol.longestSpecialPath(edges, nums))