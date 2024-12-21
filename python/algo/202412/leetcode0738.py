# 贪心专题 - 字典序最小/最大
class Solution:
    def monotoneIncreasingDigits(self, n: int) -> int:
        # 自行解答
        sn = [int(d) for d in str(n)]
        m = len(sn)

        ans = [0] * m
        ans[-1] = sn[-1]
        for i in range(m-2, -1, -1):
            if sn[i] <= ans[i+1]:
                ans[i] = sn[i]
            else:
                ans[i] = sn[i]-1
                for j in range(i+1, m):
                    ans[j] = 9
        
        return  sum(v*(10**(m-i-1)) for i, v in enumerate(ans))
