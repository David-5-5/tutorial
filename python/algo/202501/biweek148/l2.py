from typing import List

# 3424
class Solution:
    def minCost(self, arr: List[int], brr: List[int], k: int) -> int:
        ans1 = ans2 = 0
        for a, b, in zip(arr, brr):
            ans1 += abs(a-b)

        arr.sort()
        brr.sort()
        for a, b, in zip(arr, brr):
            ans2 += abs(a-b)

        return min(ans1, ans2+k)

        

if __name__ == "__main__":
    sol = Solution()
    print(sol)