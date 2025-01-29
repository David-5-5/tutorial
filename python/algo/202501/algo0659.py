from typing import List

# 贪心专题 - 构造题
class Solution:
    def isPossible(self, nums: List[int]) -> bool:
        cnt = [0] * 2004
        seq = [0] * 2004
        for x in nums:
            cnt[x+1000] += 1
        
        for x in nums:
            x += 1000
            if cnt[x] == 0: continue
            if x>0 and seq[x-1]:
                seq[x-1] -= 1
                seq[x] += 1
                cnt[x] -= 1
            else:
                if cnt[x+1] and cnt[x+2]:
                    seq[x+2] += 1
                    cnt[x] -= 1
                    cnt[x+1] -= 1
                    cnt[x+2] -= 1
                else: return False

        return True