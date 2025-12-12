from functools import cache


class Solution:
    def maxPartitionsAfterOperations(self, s: str, k: int) -> int:
        @cache
        def dfs(i:int, mask:int, changed:bool) -> int:
            if i == len(s): return 1

            bit = ord(s[i]) - ord('a')

            # not change
            res = 0
            if (mask | 1 << bit).bit_count() > k:
                res = dfs(i+1, 1<<bit, changed) + 1
            else: res = dfs(i+1, mask | 1 << bit, changed)

            # change it
            if changed: return res
            for j in range(26):
                if j == bit: continue
                # 犯了弱智错误， "=" 写成 "=="
                # newmask == mask | 1 << j 引以为戒
                if (mask | 1 << j).bit_count() > k:
                    res = max(res, dfs(i+1, 1 << j, True) + 1)
                else: res = max(res, dfs(i+1, mask | 1 << j, True))
            return res
        
        return dfs(0, 0, False)