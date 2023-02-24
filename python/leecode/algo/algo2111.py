class Solution:
    def kIncreasing(self, arr, k: int) -> int:
        def lengthOfLIS2(nums) -> int:
            n = len(nums)
            dp = [1] * n
            for i in range(n-1, -1, -1):
                for j in range(i+1, n):
                    if nums[i] <= nums[j]:
                        dp[i] = max(dp[i], dp[j]+1)
            return max(dp)
            
        def lengthOfLIS(nums) -> int:
            d = []
            for n in nums:
                if not d or n >= d[-1]:
                    d.append(n)
                else:
                    l, r = 0, len(d) - 1
                    loc = r
                    while l <= r:
                        mid = (l + r) // 2
                        if d[mid] > n:
                            loc = mid
                            r = mid - 1
                        else:
                            l = mid + 1
                    d[loc] = n
            return len(d)

        kg = [[] for _ in range(k)]
        n = len(arr)
        for i in range(n):
            kg[i % k].append(arr[i])
        chC = 0
        for i in range(k):
            chC += len(kg[i]) - lengthOfLIS(kg[i])
        return chC

if __name__ == "__main__":
    sol = Solution()
    arr, k = [12,6,12,6,14,2,13,17,3,8,11,7,4,11,18,8,8,3], 1
    # arr, k = [2,2,2,2,2,1,1,4,4,3,3,3,3,3], 1
    print(sol.kIncreasing(arr, k))