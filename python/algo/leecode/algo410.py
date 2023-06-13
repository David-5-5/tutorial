class Solution:
    def splitArray(self, nums, k: int) -> int:
        n = len(nums)
        f = [[10**18]* (k + 1) for _ in range(n + 1)]
        f[0][0] = 0
        sub = [0]
        for elem in nums:
            sub.append(sub[-1] + elem)
        
        for i in range(1, n + 1):
            for j in range(1, min(i, k) + 1):
                for p in range(i):
                    f[i][j] = min(f[i][j], max(f[p][j - 1], sub[i] - sub[p]))
        
        return f[n][k]

    def splitArray2(self, nums, k: int) -> int:

        def check(x: int) -> bool:
            total, cnt = 0, 1
            for num in nums:
                if total + num > x:
                    cnt += 1
                    total = num
                else:
                    total += num
            return cnt <= k


        left = max(nums)
        right = sum(nums)
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1

        return left



if __name__ == "__main__":
    sol = Solution()

    nums = [7,2,5,10,8]
    print(sol.splitArray2(nums, 5))