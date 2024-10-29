from typing import List


class Solution:
    def lengthAfterTransformations(self, s: str, t: int, nums: List[int]) -> int:
        # 矩阵快速幂
        # 26 * 1 的二维矩阵，用于后续的矩阵乘法
        cnt = [[0] for _ in range(26)] 
        for ch in s:
            cnt[ord(ch)-ord('a')][0] += 1
        MOD = 10 ** 9 + 7
        
        # 从初始向量 cnt 和 一次转换的目标向量(特例)，倒推出转换矩阵
        # trans (n*n) * cnt (n*1) = target (n*1)
        # 以下是计算转换矩阵
        trans = [[0] * 26 for _ in range(26)]
        for i, v in enumerate(nums):
            for sh in range(1, v+1):
                trans[(i+sh) % 26 ][i] = 1

        # 矩阵乘法
        def pow(a:List[List[int]], b:List[List[int]]) -> List[List[int]]:
            r, m, c = len(a), len(a[0]), len(b[0])
            res = [[0] * c for _ in range(r)]
            for i in range(r):
                for j in range(c):
                    for k in range(m):
                        res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD
            return res
        
        # 初始值 矩阵 I 相当于 1 
        ans = [[1 if i==j else 0 for i in range(26)] for j in range(26)] 
        while t:
            if t & 1 == 1:
                ans = pow(trans, ans)
            trans = pow(trans, trans)
            t = t >> 1
        
        return sum(sum(i) for i in pow(ans, cnt))  % MOD
    
if __name__ == "__main__":
    sol = Solution()
    s, t, nums = "abcyy", 2, [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
    s, t = "jqktcurgdvlibczdsvnsg", 7517
    print(sol.lengthAfterTransformations(s, t, nums))