from collections import Counter
from typing import List

# 贪心专题 相邻不同 证明/构造方案
class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        cnt = Counter(tasks)

        m = len(tasks)

        mx_cnt = max(cnt.values())
        if m >= mx_cnt * (n + 1): return m

        ans = (mx_cnt - 1) * (n+1)
        s_cnt = sorted(cnt.values(), reverse=True)
        for cnt in s_cnt[0:n]:
            if cnt == mx_cnt: ans += 1
        
        return max(ans, m)
    
if __name__ == "__main__":
    sol = Solution()
    tasks, n = ["A","A","A","B","B","B"], 2
    tasks, n = ["A","B","C","D","A","B","V"], 3
    print(sol.leastInterval(tasks, n))