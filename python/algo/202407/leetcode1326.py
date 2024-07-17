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

if __name__ == "__main__":
    sol = Solution()
    n, ranges = 5, [3,4,1,1,0,0]
    n, ranges = 202, [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 1, 1, 1, 1]
    print(sol.minTaps(n, ranges))
    print(sol.minTaps2(n, ranges))