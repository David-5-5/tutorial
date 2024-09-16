from cmath import inf
from typing import List


class Solution:
    # 自行解答, 思维要求高
    def totalSteps(self, nums: List[int]) -> int:
        nums.append(inf) # 哨兵
        # 单调栈，元素 [数组元素，删除后面元素的次数]，按数组元素递减
        # 当新数组值大于等于栈顶元素时：
        # 1、循环
        #   1.1、栈顶出栈，
        #   1.2、更新下一个栈顶元素的删除次数，规则见代码(关键)
        # 3、新元素进栈
        ans, st = 0, []
        for v in nums:
            while st and st[-1][0] <= v:
                _, cnt = st.pop(-1)
                ans = max(ans, cnt)
                if st: st[-1][1] = max(cnt, st[-1][1] + 1)
            st.append([v, 0])
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums = [1682,63,124,147,897,1210,1585,1744,1764,1945,323,984,1886,346,481,1059,1388,1483,1516,1842,1868,1877,504,1197,785,955,970,1848,1851,398,907,995,1167,1214,1423,1452,1464,1474,1311,1427,1757,1992,57,1625,1260,700,725]
    # nums = [1682,63,124,1945,300,600,900,323,984,1886,324,985,1887,1888]
    # nums = [10,15,13,1,10]
    print(sol.totalSteps(nums))