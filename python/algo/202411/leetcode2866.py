from tkinter import N
from typing import List

# 周赛 364
class Solution:
    def maximumSumOfHeights(self, maxHeights: List[int]) -> int:
        # 参考题解
        n = len(maxHeights)

        suf = [0] * (n+1)

        ssuf, st = 0, [n]
        for i in range(n-1, -1, -1):
            x = maxHeights[i]
            while len(st)>1 and maxHeights[st[-1]] >= x:
                j = st.pop()
                ssuf -= maxHeights[j] * (st[-1] - j)
            ssuf += x * (st[-1] - i)
            suf[i] = ssuf
            st.append(i)

        pre = [0] * n

        spre, st = 0, [-1]
        for i in range(n):
            x = maxHeights[i]
            while len(st)>1 and maxHeights[st[-1]] >= x:
                j = st.pop()
                spre -= maxHeights[j] * (j - st[-1])
            spre += x * (i - st[-1])
            pre[i] = spre
            st.append(i)

        ans = 0
        for i in range(n):
            if pre[i] + suf[i+1] > ans: ans = pre[i] + suf[i+1]
        return ans


if __name__ == "__main__":
    sol = Solution()
    maxHeights = [5,3,4,1,1]
    print(sol.maximumSumOfHeights(maxHeights))