class Solution:
    def jobScheduling(self, startTime, endTime, profit) -> int:
        n = len(startTime)
        dp = [0] * (n + 1)
        from bisect import bisect_right
        tasks = sorted(zip(startTime, endTime, profit), key= lambda p:p[1])
        endTime.sort()
        for i in range(n):
            k = bisect_right(endTime, tasks[i][0])
            # key paramater is supported since python3.10
            # The code is concise but the performance is bad.
            # k = bisect_right(tasks, tasks[i][0], hi=i, key=lambda p: p[1])
            dp[i+1] = max(dp[i], dp[k]+tasks[i][2])

        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    startTime, endTime, profit = [1,2,3,3], [3,4,5,6], [50,10,40,70]
    startTime, endTime, profit = [1,2,3,4,6], [3,5,10,6,9], [20,20,100,70,60]
    print(sol.jobScheduling(startTime, endTime, profit))