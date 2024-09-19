# 周赛 298
class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        # 参考题解，贪心
        m = k.bit_length()
        ans = m - 1 # m-1 位长度肯定小于 k
        # 记录 k 101, s = 11.101.10, ans = 2 + 前导 0, 101 中的零一定可以加到最后 2 位上
        if int(s[-m:],2) <= k: ans = m # s[-m:] 表示字符串中最后 m 个元素
        return ans + s[:-m].count('0') # s[:-m] 表示字符串中除出最后 m 个元素