from bisect import bisect_left
from typing import List

# 周赛 297
class Solution:
    def distributeCookies(self, cookies: List[int], k: int) -> int:
        # 同 1723
        def check(limit):
            workloads = [0] * k
            return backtrack(workloads, 0, limit)

        def backtrack(workloads, i, limit):
            if i >= len(cookies):
                return True
            cur = cookies[i]
            for j in range(len(workloads)):
                if workloads[j] + cur <= limit:
                    workloads[j] += cur
                    if backtrack(workloads, i + 1, limit):
                        return True
                    workloads[j] -= cur
                if workloads[j] == 0 or workloads[j] + cur == limit:
                    break
            return False
        
        cookies.sort(reverse=True)
        l, r = max(cookies), sum(cookies)
        # while l < r:
        #     mid = (l + r) >> 1
        #     if check(cookies, k, mid):
        #         r = mid
        #     else:
        #         l = mid + 1
        # return l 
        return bisect_left(range(l, r), True, key=check) + l

if __name__ == "__main__":
    sol = Solution()
    cookies, k = [8,15,10,20,8], 2
    print(sol.distributeCookies(cookies, k)) 