from typing import List
class Solution:
    def getCollisionTimes(self, cars: List[List[int]]) -> List[float]:
        # 解题思路
        # 若当前元素的速度小于栈顶元素，则当前元素无法与栈顶元素相遇，栈顶元素出栈
        # 若栈顶元素小于当前元素，计算栈顶元素变速前，若不相遇，则当前元素行进的时间
        # 变速后（不断在栈中寻找前一个元素）按照变速后的时间继续分段计算
        n = len(cars)
        ans = [-1] * n
        st = []
        cars.reverse()
        for i, [pos, speed] in enumerate(cars):
            dynp, begin = pos, 0
            while st and st[-1][0] >= speed:
                st.pop()

            if not st:
                st.append([speed, pos, -1])
            else:
                sp,j = speed, 0
                # 若栈顶元素小于当前元素，计算栈顶元素变速前的位置变化
                while st[-1-j][2] != -1 and dynp + sp * (st[-1-j][2]-begin) < st[-1-j][0] * st[-1-j][2] + st[-1-j][1]:
                    dynp += sp * (st[-1][2]-begin)
                    begin, j = st[-1][2], j+1

                ans[n-1-i] = begin + (st[-1-j][1]+st[-1-j][0]*begin-dynp)/(sp - st[-1-j][0])
                st.append([speed, pos, ans[n-1-i]])
        
        return ans

    def getCollisionTimes2(self, cars: List[List[int]]) -> List[float]:
        # 优化方案，分段计算不必要，直接将栈顶元素出栈，与下一个元素比较
        # [[3,4],[6,3],[9,1]]
        # [6,3]在1.5秒后与[9,1]在位置10.5的位置相遇
        # [3,4]在1.5秒后位置在9,与[6,3]此时在10.5,后续变速为1，忽略[6,3]
        # 直接计算[3,4]与[9,1]的相遇时间即可
        n = len(cars)
        ans = [-1] * n
        st = []
        cars.reverse()
        for i, [pos, speed] in enumerate(cars):
            while st and st[-1][0] >= speed:
                st.pop()

            if not st:
                st.append([speed, pos, -1])
            else:
                while st[-1][2] != -1 and pos + speed * st[-1][2] < st[-1][0] * st[-1][2] + st[-1][1]:
                    # 若当前位置的车队前行，在栈顶元素初始的时间内未相遇（后续降速），
                    # 则栈顶元素出栈，并与前一个元素之间比较
                    st.pop()
                # 计算与在前一个元素的变速前的时间内，相遇的时间点
                ans[n-1-i] = (st[-1][1]-pos)/(speed - st[-1][0])
                st.append([speed, pos, ans[n-1-i]])
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    cars = [[1,2],[2,1],[4,3],[7,2]]
    cars = [[3,4],[5,4],[6,3],[9,1]]
    print(sol.getCollisionTimes(cars))
