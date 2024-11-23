from collections import Counter
from typing import List

# 贪心专题
class Solution:
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        # 自行解答
        cnt = Counter(arr)

        ans = len(cnt)
        # 按出现次数从小到大排序，尽量减去出现次数小的数字
        # 这样剩下的不同整数的数目最少
        for _, v in sorted(cnt.items(), key=lambda p:p[1]):
            if k >= v:
                k -= v
                ans -= 1
            else:
                break
        return ans

if __name__ == "__main__":
    sol = Solution()
    arr, k = [4,3,1,1,3,3,2], 3
    print(sol.findLeastNumOfUniqueInts(arr, k))