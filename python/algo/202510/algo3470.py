from typing import List

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        # 按题意解答
        k -= 1 #计算更加方便

        # 不够精确, 保证不超过 k 太多, 后续选择divmod的操作令 j = 0 即可
        def perm(left: int) -> int:
            if left <= 2: return 1

            half = left // 2
            res = 1
            for i in range(2, half+1):
                res *= i * i
                if res > k and i < half: return res * (half+1 if left % 2 else half)
            if left % 2: res *= half+1
            return res

        if (n%2 and k >= perm(n)) or (n%2==0 and k >= 2*perm(n)): return []

        cand = [list(range(2,n+1,2)), list(range(1,n+1,2))]

        ans = []
        prev = 1
        for i in range(n):
            j = 0
            if i == 0:
                if n % 2: 
                    prev = 0 # 奇数, 前一个设置为偶数
                    j, k = divmod(k, perm(n)//(n//2 + 1))
                else:
                    j, k = divmod(k, 2*perm(n)//n)
                    j, prev = divmod(j, 2)
            else:
                j, k = divmod(k, perm(n-i)//len(cand[prev^1]))
            
            prev ^= 1
            ans.append(cand[prev].pop(j))

        return ans

if __name__ == "__main__":
    print(Solution().permute(4, 6))