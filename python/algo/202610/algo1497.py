class Solution:
    def canArrange(self, arr: list[int], k: int) -> bool:
        cnt = [0] * k

        for v in arr:
            if (cnt[(k - v%k)%k]): cnt[(k - v%k)%k] -= 1
            else: cnt[v%k] += 1
        

        if any(x for x in cnt): return False
        else: return True