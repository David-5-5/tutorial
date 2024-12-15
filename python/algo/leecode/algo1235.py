from typing import List

# DP专题 - 不相交区间； 2024.12 复习
class Solution:
    def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:
        # 由于 startTime和endTime取值范围为 10 ^ 9, 不用分组(2830,2008)
        # 按照右节点排序
        n = len(startTime)
        dp = [0] * (n + 1)
        from bisect import bisect_right
        tasks = sorted(zip(startTime, endTime, profit), key= lambda p:p[1])
        endTime.sort()
        for i in range(n):
            # 确定状态转移的上一个状态值(下标)
            k = bisect_right(endTime, tasks[i][0]) # 当前起始时间的在endtime数组中下标，
            
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