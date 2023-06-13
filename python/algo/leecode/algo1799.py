class Solution:
    def maxScore(self, nums) -> int:
        # Python code to demonstrate naive
        # method to compute gcd (Loops)
        def computeGCD(x, y):
            while(y):
                x, y = y, x % y
            return abs(x)

        def contains(state, i):
            return state & 1 << i > 0
        
        def substact(state, i, j):
            return state ^ (1 << i) ^ (1 << j)
        
        def calDp(state, lens):
            if dp[state] != -1:return dp[state]
            maxScore = 0
            for i in range(m):
                for j in range(i+1, m):
                    if contains(state, i) and contains(state, j):
                        maxScore = max(maxScore, gcds[(i,j)] * lens // 2 + calDp(substact(state, i, j), lens-2))
            dp[state] = maxScore
            return maxScore

        m = len(nums)
        gcds = {}

        for i in range(m):
            for j in range(i+1, m):
                gcds[(i,j)] = computeGCD(nums[i], nums[j])

        state = 1 << m
        dp = [-1] * state
        dp[0] = 0
        ret = calDp(state - 1, m)
        return ret

if __name__ == '__main__':
    sol = Solution()
    nums = [984916,312350,779975,165893,436389,592384,264617,136726,8893,587955,921403,891842]
    # nums = [415,230,471,705,902,87]
    from datetime import datetime
    begin = datetime.now()
    print(sol.maxScore(nums))
    print((datetime.now()- begin).total_seconds())