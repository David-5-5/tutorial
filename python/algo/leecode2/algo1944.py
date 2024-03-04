from typing import List
class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        # 引入单调递减栈
        st = []

        ans = [0] * len(heights)
        for i, h in enumerate(heights):
            # 若栈顶元素小于当前元素，则当前元素出栈，
            # 当前元素下标 - 栈顶元素下标，即为栈顶元素的能看右边的长度
            # ！！！！！ IMPORT !!!!!!!!!!
            # 值得注意的是，当栈顶元素出栈后，后一个栈顶元素，无法看到
            # 刚出栈栈顶元素和当前元素中间的数量，因此预先减去中间元素的数量
            # 例如 [10,6,8,5,11,9]
            # stack [10 8 5], 11待进栈时，
            # 1, 5出栈[10 8]，能看到长度为 4-3 =1，元素8 ans[2] -= 4 - 3 - 1
            # 2, 8出栈[10], 能看长度为2, ans[2] += 4 - 2 ，ans[2] = 2, 
            #    同时元素8 ans[0] -= 4 - 2 - 1 = ans[0] = -1
            # 3, 10出栈[], ans[0] = -1 则 ans[0] += 4 - 0 = 3
            #    从10无法看到8和11中间的5
            while st and heights[st[-1]] <= h:
                inx = st.pop()
                ans[inx] += i - inx
                # 预先减去中间元素的数量
                if st: ans[st[-1]] -= i - inx - 1
            st.append(i)
        
        # 若剩余最后的列表，加上相邻两个元素的下标差
        prev = 0
        if st: prev = st[-1]
        while st:
            inx = st.pop()
            ans[inx] += prev - inx
            prev = inx
        return ans

if __name__ == "__main__":
    sol = Solution()
    heights = [9,8,6,7]
    print(sol.canSeePersonsCount(heights))