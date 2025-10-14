from collections import defaultdict

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        # 参考题解，递归也考虑到了，担心超时
        # 技巧：
        # 1，找到第一个不满足要求的字符就递归
        # 2，不需要记录每个字符的字符串序列
        def dfs(l:int, r:int) -> int:
            if r - l < k: return 0
            cnt = defaultdict(int)
            for i in range(l, r):
                cnt[s[i]] += 1
            
            res, find = 0, ''
            for ch, v in cnt.items():
                if v < k:
                    find = ch
                    break

            if find != '': 
                prev = l
                for i in range(l, r):
                    if s[i] == find:
                        res = max(res, dfs(prev, i))
                        prev = i + 1
                res = max(res, dfs(prev, r))
            
            return r - l if find == '' else res
        return dfs(0, len(s))
    