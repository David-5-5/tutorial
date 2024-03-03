from typing import List
class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        # 包含两个通用方法:
        # 1) 使用单调栈，求解数组中每个元素在为子数组最小/大值的边界，时间复杂度 O(N)
        #    初始化长度都为N的left(初始值为-1), right(初始值为N)数组，
        #    重复当前元素与栈顶元素比较
        #    若 栈顶元素 >= 当前元素，则栈顶元素出栈，其元素的right为当前元素的下标
        #    直至 栈为空 或 栈顶元素 < 当前元素
        #    设置当前元素的left为栈顶元素下标，当前元素的下标进栈。
        #    举例说明:
        #      i  0 1 2 3 4 4 5 7 8 9
        #         4 7 8 5 4 6 9 8 3 4 ...
        #    i=1  l i   r  
        #    i=4  l       i         r
        #    对于i=0
        #       a) 元素7，7 > 4 当其栈时，设置left[1] = 0， 
        #       b) 当下标i=3元素5进栈时，元素7,8出栈，设置right[1]=3
        #    对于i=4, 
        #       a) 当元素进栈，比较条件是 >= 因此所有元素出栈， left[4] = -1
        #       b) 当下标i=9元素4元素进栈，栈顶元素出栈 right[4] = 9
        #    最后各元素i的 [left[i] + 1, right[i] -1] 即为元素的最小值区间
        #    i = 1, 下标 [1,2] 即 元素[7 8]为元素7的区间
        #    i = 4  下标 [0,8] 即 元素[4 7 8 5 4 6 9 8 3]元素4的区间，
        #    注： 元素相等时，仅包含左区间，以避免重复计算
        # 2) 各元素i为最小值的[L,R]区间中的子数组数量
        #    [7 8] 的子数组 [7] [7, 8]
        #    [4 7 8 5 4 6 9 8 3],为 (i-left+1)*(right-i+1)
        MOD = 10 ** 9 + 7
        n = len(arr)
        left, right, st = [-1] * n, [n]* n, []
        for i, v in enumerate(arr):
            while st and arr[st[-1]] >= v: right[st.pop()] = i
            if st: left[i] = st[-1]
            st.append(i)
        ans = 0
        for i, v in enumerate(arr):
            p, q = right[i] - i, i-left[i]
            ans =  (ans + v * p * q) % MOD
        return ans

if __name__ == "__main__":
    sol = Solution()
    arr = [11,81,94,43,3]
    print(sol.sumSubarrayMins(arr))