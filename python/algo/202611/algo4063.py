class Solution:
    def longestSubarray(self, nums: list[int], k: int) -> int:
        ans, n = 0, len(nums)
        for i in range(n):
            rem, pres = set(), 0
            if n - i < ans: break
            def check(x: int) -> bool:
                r = x % k
                if r == 0: return True
                if r % 2 == 0 and r // 2 in rem:
                    return True
                if (r + k) % 2 == 0 and (r + k) // 2 in rem:
                    return True
                return False
            for j in range(i, n):
                x = nums[j]
                pres += x
                rem.add(x % k)
                if check(pres):
                    if j - i + 1 > ans: ans = j - i + 1
        return ans