from typing import List


class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:

        idx = [0] * n
        for i, j in enumerate([i for i, _ in sorted(enumerate(nums), key=lambda p:p[1])]):
            idx[j] = i
        
        nums.sort()
        m = n.bit_length() + 1
        
        dp = [[-1] * m for _ in range(n)]

        i, j = 0, 0
        while i < n:
            while j<n-1 and nums[j+1] - nums[i] <= maxDiff:
                j += 1
            dp[i][0] = j
            i += 1
        
        for j in range(1, m):
            for i in range(n):
                p = dp[i][j-1]
                # if p == -1 or i == p: continue
                dp[i][j] = dp[p][j-1]

        ans = [-1] * len(queries)

        for i, [u, v] in enumerate(queries):
            if u == v: ans[i] = 0
            else:
                l, r = idx[u], idx[v]
                if nums[l] > nums[r]:
                    l, r = r, l
                res = 0
                while True:
                    j = m-1
                    while j>=0 and (dp[l][j] == -1 or (j and nums[dp[l][j-1]] >= nums[r])):
                        j -= 1
                        # print(l, j, r, j>=0 and dp[l][j] == -1)
                    if j == -1 or nums[dp[l][j]] < nums[r]: break
                    if j > 1:
                        res += 1 << (j-1)
                        l = dp[l][j-1]
                    else:
                        res += 1 << j
                        ans[i] = res
                        break
        return ans        

    def pathExistenceQueries2(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:
        # 优化 倍增
        idx = [0] * n
        for i, j in enumerate([i for i, _ in sorted(enumerate(nums), key=lambda p:p[1])]):
            idx[j] = i
        
        nums.sort()
        m = n.bit_length() + 1
        dp = [[-1] * m for _ in range(n)]

        i, j = 0, 0
        while i < n:
            while j<n-1 and nums[j+1] - nums[i] <= maxDiff:
                j += 1
            dp[i][0] = j
            i += 1
        
        for j in range(1, m):
            for i in range(n):
                p = dp[i][j-1]
                dp[i][j] = dp[p][j-1]

        ans = [-1] * len(queries)

        for i, [u, v] in enumerate(queries):
            if u == v:
                ans[i] = 0
                continue

            l, r = idx[u], idx[v]  
            if l > r:  # nums有序，用 l r 索引替换 nums
                l, r = r, l
            res = 0
            for j in range(m-1, -1, -1):
                if dp[l][j] < r:
                    res += 1 << j
                    l = dp[l][j]
            ans[i] = res + 1 if dp[l][0] >= r else -1
        return ans
    

if __name__ == "__main__":
    print(Solution().pathExistenceQueries2(29, [72865,64390,33154,31102,24466,27009,49227,52370,98159,39688,84981,89334,31482,32999,58937,73885,98036,69943,46770,65206,83244,56745,75337,7973,81408,96338,643,64717,54936], 19318, [[23,25],[2,14],[9,27],[26,10],[5,25],[7,27],[1,6],[23,28],[7,21],[12,18]]))