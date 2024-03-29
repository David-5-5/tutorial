import heapq
class Solution:
    def minimumTimeRequired(self, jobs, k):
        '''
        
        '''
        def check(jobs, k, limit):
            workloads = [0] * k
            return backtrack(jobs, workloads, 0, limit)

        def backtrack(jobs, workloads, i, limit):
            if i >= len(jobs):
                return True
            cur = jobs[i]
            for j in range(len(workloads)):
                if workloads[j] + cur <= limit:
                    workloads[j] += cur
                    if backtrack(jobs, workloads, i + 1, limit):
                        return True
                    workloads[j] -= cur
                if workloads[j] == 0 or workloads[j] + cur == limit:
                    break
            return False
        
        jobs.sort(reverse=True)
        l, r = jobs[0], sum(jobs)
        while l < r:
            mid = (l + r) >> 1
            if check(jobs, k, mid):
                r = mid
            else:
                l = mid + 1
        return l

    def minimumTimeRequired2(self, jobs, k: int) -> int:
        n = len(jobs)
        sum = [0] * (1 << n)
        for i in range(1, 1 << n):
            x = bin(i)[::-1].index('1')
            y = i - (1 << x)
            sum[i] = sum[y] + jobs[x]

        dp = [[0] * (1 << n) for _ in range(k)]
        for i in range(1 << n):
            dp[0][i] = sum[i]

        for i in range(1, k):
            for j in range(1 << n):
                minn = float('inf')
                x = j
                while x:
                    minn = min(minn, max(dp[i - 1][j - x], sum[x]))
                    x = (x - 1) & j
                dp[i][j] = minn

        return dp[k - 1][(1 << n) - 1]


    def minimumTimeRequiredApproximate(self, jobs, k: int) -> int:
        works = []
        for i in range(k):
            heapq.heappush(works, 0)
        jobs.sort(reverse=True)
        for job in jobs:
            _job = heapq.heappop(works) + job
            heapq.heappush(works, _job)
        
        return max(works)

if __name__ == '__main__':
    sol = Solution()
    jobs = [331,769,967,535,243,239,529,102,250,469,261,283,280,280,280]
    # jobs = [331,769,967,535,243,239,529,102,250,469,261,283,280,280,280,331,769,967,535,243,239,529,102,250,469]
    k = 10
    from datetime import datetime
    begin = datetime.now()
    print(sol.minimumTimeRequired(jobs, k))
    print((datetime.now()- begin).total_seconds())

    # begin = datetime.now()
    # print(sol.minimumTimeRequired2(jobs, k))
    # print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    print(sol.minimumTimeRequiredApproximate(jobs, k))
    print((datetime.now()- begin).total_seconds())