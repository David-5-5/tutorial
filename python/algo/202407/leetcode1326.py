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
        # 对 minTaps 重新整理了区间的包含关系
        st = []
        for i, v in enumerate(ranges):
            l,r = max(0, i-v), min(n, i+v)
            
            # 以下三种情况，则忽略该元素
            # - 当前区间的 l > 栈顶右端点 r，即与当前元素无交集
            # - 当前区间的 r < 栈顶右端点 r，不能增加右端点区间
            # - 当前区间是栈顶区间子集
            if st and (l > st[-1][1] or r < st[-1][1] or (l >= st[-1][0] and r <= st[-1][1]) ) : 
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

        
    def minTaps4(self, n: int, ranges: List[int]) -> int:
        # 参考题解，rightMost
        rightMost = [0] * (n+1)
        for i, r in enumerate(ranges):
            l = max(0, i-r)
            rightMost[l] = max(rightMost[l], i + r)

        ans, cur_right, next_right = 0, 0, 0
        for i in range(n):
            next_right = max(next_right, rightMost[i])
            if i == cur_right: # i < 当前已达到的右端点时忽略
                if i == next_right: return -1
                
                cur_right = next_right
                ans += 1
        return ans


if __name__ == "__main__":
    sol = Solution()
    n, ranges = 5, [3,4,1,1,0,0]
    n, ranges = 9, [0,5,0,3,3,3,1,4,0,4]
    print(sol.minTaps(n, ranges))
    print(sol.minTaps2(n, ranges))