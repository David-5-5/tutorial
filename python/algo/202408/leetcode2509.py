from typing import List

# 周赛 324 最近公共祖先
# 根结点为 1 开始编号的完全二叉树，结点 i 的子结点编号 2*i， 2*i+1
# 因此 结点 i // 2 即为其父结点
class Solution:
    def cycleLengthQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        ans = [1]  * len(queries)
        for i, (u, v) in enumerate(queries):
            while True:
                if u == v: break  # 找到最近祖先结点
                ans[i] += 1
                if u > v: # 对于编号大的结点，首先求其父结点
                    u //= 2 # 计算 u 的父结点
                else:
                    v //= 2 # 计算 v 的父结点
        return ans           

if __name__ == "__main__":
    sol = Solution()
    n, queries = 3, [[5,3],[4,7],[2,3]]
    print(sol.cycleLengthQueries(n, queries))