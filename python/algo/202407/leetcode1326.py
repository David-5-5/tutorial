from cmath import inf
from typing import List

class Solution:
    def minTaps(self, n: int, ranges: List[int]) -> int:
        ''' Pass 
        '''
        st = []
        for i, v in enumerate(ranges):
            l,r = max(0, i-v), min(n, i+v)

            if st and l >= st[-1][0] and r <= st[-1][1]: # 当前范围包含在栈顶范围内
                continue

            while st and l <= st[-1][0] and r >= st[-1][1] :
                st.pop()
            
            if not st or  (l <= st[-1][1] and r > st[-1][1]): # 和栈顶的 right 不重叠, 忽略该元素
                left = st[-1][1] if st else l
                st.append((left,r))
        
        if st and st[-1][1] == n:
            return len(st)
        else:
            return -1
        
    def minTaps2(self, n: int, ranges: List[int]) -> int:
        st = []
        for i, v in enumerate(ranges):
            l,r = max(0, i-v), min(n, i+v)

            # 如果 当前范围包含在栈顶范围内 或者 [l,r] 和栈顶的 right 不重叠，则忽略该元素
            if st and (l > st[-1][1] or l >= st[-1][0] and r <= st[-1][1] ) : 
                continue

            while st and l <= st[-1][0] and r >= st[-1][1]:
                st.pop()

            left = st[-1][1] if st else l
            st.append((left,r))
        
        if st and st[-1][1] == n:
            return len(st)
        else:
            return -1
        

    def minTaps3(self, n: int, ranges: List[int]) -> int:
        # 参考题解，动态规划 时间复杂度 O(n*(logn + max(ranges)))
        # 注： 本题中 n <= 10 ^ 4, ranges[i] <= 100
        #     当 max(range) 接近 n 时，时间复杂度为 O(n^2)，应会超时
        intervals = []
        for i, v in enumerate(ranges):
            start = max(0, i-v)
            end = min(n, i+v)
            intervals.append((start, end))
        intervals.sort()

        dp = [inf] * (n+1)
        dp[0] = 0
        for start, end in intervals:
            if dp[start] == inf:
                return -1
            for i in range(start, end+1):
                dp[i] = min(dp[i], dp[start]+1)
        return dp[n]

        
if __name__ == "__main__":
    sol = Solution()
    n, ranges = 5, [3,4,1,1,0,0]
    print(sol.minTaps(n, ranges))
    print(sol.minTaps3(n, ranges))