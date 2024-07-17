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



if __name__ == "__main__":
    sol = Solution()
    n, ranges = 5, [3,4,1,1,0,0]
    # n, ranges = 5, [1,1,1,1,2,9]
    print(sol.minTaps(n, ranges))
    print(sol.minTaps2(n, ranges))