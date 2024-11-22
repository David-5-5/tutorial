from typing import List

# 贪心专题
class Solution:
    def maxCount(self, banned: List[int], n: int, maxSum: int) -> int:
        # 编程题，必须用 set 替换 list
        ban = set(banned)
        ans = tot = 0
        for i in range(1, n+1):
            if i in ban:continue # O(logN), 如果是 list O(N)
            if tot + i > maxSum:break
            tot += i
            ans += 1
        return  ans

if __name__ == "__main__":
    sol = Solution()
    banned, n, maxSum = [1,6,5], 5, 6
    print(sol.maxCount(banned, n, maxSum))