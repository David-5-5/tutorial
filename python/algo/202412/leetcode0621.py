from collections import Counter
from typing import List

# 贪心专题 相邻不同 证明/构造方案
class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        # 自行解答
        # 思路： 从 n=1 说起(leetcode 767)，即相邻的字母需要不同，出现次数最多字母次数为 mx_cnt，则字符长度至少需要 (mx_cnt-1) * 2 + 1
        #           如果不满足，中间保留空位，长度即为 (mx_cnt-1) * 2 + 1
        #       对 n>1 的情况，这样需要考察 n 个出现次数最多字母次数，出现次数最多的字母，
        #       出现次数最多的第1个字母, 最后的位置长度应为 (mx_cnt-1) * (n+1) + 1
        #       出现次数一样多第2个字母，最后的位置长度 (mx_cnt-1) * (n+1) + 2
        #        ...        ...
        #       出现次数一样多第n个字母，最后的位置长度 (mx_cnt-1) * (n+1) + n (最多检查n个)
        # 最后取 max((mx_cnt-1) * (n+1) + x, len(task)) 其中 x 个出现次数最多的字母(出现次数相同)
        # 
        cnt = Counter(tasks)

        m = len(tasks)

        mx_cnt = max(cnt.values())

        ans = (mx_cnt - 1) * (n+1)
        s_cnt = sorted(cnt.values(), reverse=True)
        for cnt in s_cnt[0:n]:
            if cnt == mx_cnt: ans += 1
            else: break
        
        return max(ans, m)

        # 同官方题解构造方法的思路一致, 以下是官方题解的代码
        # freq = collections.Counter(tasks)

        # # 最多的执行次数
        # maxExec = max(freq.values())
        # # 具有最多执行次数的任务数量
        # maxCount = sum(1 for v in freq.values() if v == maxExec)

        # return max((maxExec - 1) * (n + 1) + maxCount, len(tasks))

    
if __name__ == "__main__":
    sol = Solution()
    tasks, n = ["A","A","A","B","B","B"], 2
    tasks, n = ["A","B","C","D","A","B","V"], 3
    print(sol.leastInterval(tasks, n))