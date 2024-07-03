from typing import List
# 树形DP
# 最长路径，就是父节点和最长的两个子树的长度之和，即选取最长的两个子树结点
# dfs[i] = max(dfs(children[i]))
# 限制条件，两个相邻节点的字符不同，
# 字符相同，不更新最大值，但是不影响递归，因为子树内部可能存在最长路径
# 最后 返回值 + 1, 按题意是组成边的节点数量
class Solution:
    def longestPath(self, parent: List[int], s: str) -> int:
        n = len(parent)
        g = [[] for _ in range(n)]
        for i in range(1,n):
            g[parent[i]].append(i)

        ans = 0
        def dfs(x):
            nonlocal ans
            x_len = 0
            for c in g[x]:
                y_len = dfs(c) + 1
                if s[x] != s[c]:
                    ans = max(ans, x_len + y_len)
                    x_len = max(x_len, y_len)
            return x_len
        
        dfs(0)
        return ans + 1