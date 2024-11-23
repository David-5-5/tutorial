from collections import Counter
from typing import List

# 贪心专题
class Solution:
    def minSetSize(self, arr: List[int]) -> int:
        # 自行解答 
        n, dlen, ans = len(arr), 0, 0
        cnt = Counter(arr)
        for _, v in sorted(cnt.items(), key=lambda p:-p[1]):
            ans += 1
            dlen += v
            if dlen * 2 >= n:
                break
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.minSetSize([3,3,3,3,5,5,5,2,2,7]))    


