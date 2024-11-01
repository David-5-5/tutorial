from typing import List

# 周赛 362
class Solution:
    def numberOfWays(self, s: str, t: str, k: int) -> int:
        # 参考题解：
        # 1、通过 KMP 找出匹配的次数，并给出状态转移方程 
        # 2、矩阵快速幂优化DP
        MOD = 10 ** 9 + 7
        
        # 求 模式匹配次数
        def kmp(s:str, p:str):
            m, n = len(s), len(p)
            p_pi = [0] * n

            # Inx of first char of each matches
            ans = 0

            # Compute the prefix function of p
            for i in range(1, n):
                j = p_pi[i-1]
                while j>0 and p[j] != p[i]: j = p_pi[j-1]
                if p[j] == p[i]:
                    p_pi[i] = j+1
                else:
                    p_pi[i] = j
            
            j = 0 # j 既是 pattern 索引，也是 s[i] 的 pi 值 
            for i in range(m):
                while j>0 and p[j] != s[i]: j = p_pi[j-1]
                if p[j] == s[i]:
                    j += 1

                # Find match
                if j == n:
                    ans += 1
                    j = p_pi[j-1] 
            
            return ans
        

        # 以下是题目相关代码，其他是模板
        n = len(s)
        c = kmp(s+s[0:n-1], t)
        # 初始状态
        f0 = [[1 if s == t else 0],[0 if s == t else 1]]
        # 状态转移方程的矩阵表达式
        trans = [[c-1, c], [n-c, n-c-1]]
        # 以上是题目相关代码，其他是模板

        # 矩阵快速幂 模板
        def pow(a:List[List[int]], b:List[List[int]]) -> List[List[int]]:
            r, m, c = len(a), len(a[0]), len(b[0])
            res = [[0] * c for _ in range(r)]
            for i in range(r):
                for j in range(c):
                    for k in range(m):
                        res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD
            return res
        ans = [[1 if i==j else 0 for i in range(2)] for j in range(2)]
        while k:
            if k & 1 == 1:
                ans = pow(trans, ans)
            trans = pow(trans, trans)
            k = k >> 1

        res = pow(ans, f0)
        return res[0][0]

if __name__ == "__main__":
    sol = Solution()
    s, t, k = "abcd", "cdab", 2
    s, t, k = "ceoceo", "eoceoc", 4
    print(sol.numberOfWays(s, t, k))
