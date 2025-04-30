from functools import cache
from typing import List


class Solution:
    def maxHappyGroups(self, batchSize: int, groups: List[int]) -> int:
        # 自行解答 根据 c++ 改写，python 一次通过，c++ 还没通过
        n = len(groups)
        cnt = [0] * batchSize
        for g in groups:
            cnt[g%batchSize] += 1

        @cache        
        def dfs(l:int, s:int) -> int :
            if s == 0: return 0
            res = 0
            for k in range(batchSize):
                if (s >> (5*k)) & 31:
                    res = max(res, dfs((l+k)%batchSize, s-(1<<(5*k))))
            return res + (l==0)
 
        s = 0
        for i in range(batchSize):
            s |= cnt[i] << (5*i)
        
        return dfs(0, s)