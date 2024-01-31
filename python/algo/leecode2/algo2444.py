from typing import List
class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        n = len(nums)
        begin, lastMin, lastMax = 0, -1, -1
        distincts = []

        ans = 0

        def count(begin, end):
            if not distincts:
                return 0
            ret = 0
            while distincts:
                left, right = distincts.pop(0)
                begin = min(begin, left)
                ret += (left - begin + 1) * (end + 1 - right)
                begin = left + 1
            return ret

        for i in range(n):
            if nums[i] < minK or nums[i] > maxK:
                ans += count(begin, i-1)
                begin, lastMin, lastMax = i+1, -1, -1
            if nums[i] == minK:
                lastMin = i
            if nums[i] == maxK:
                lastMax = i
            if lastMin != -1 and lastMax != -1:
                left = min(lastMin, lastMax)
                right = max(lastMin, lastMax)
                if not distincts:
                    distincts.append((left, right))
                elif distincts[-1][0] != left:
                    distincts.append((left, right))
        
        if distincts:
            ans += count(begin, n-1)
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, minK, maxK = [1,3,5,2,7,5], 1, 5
    # nums, minK, maxK = [1,3,5,2,1,5], 1, 5
    # nums, minK, maxK = [1,1,1,1], 1, 1
    # nums, minK, maxK = [1,1,5,2,1,5], 1, 5
    # nums, minK, maxK = [1,1,5,2,5,1], 1, 5
    print(sol.countSubarrays(nums, minK, maxK))