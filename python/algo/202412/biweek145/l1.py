from typing import Counter, List


class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        cnt = Counter(nums)
        ans = 0
        for v in cnt.keys():
            if v < k: return -1
            if v == k:continue
            ans += 1
        return ans

        
if __name__ == "__main__":
    sol = Solution()
    print(sol)