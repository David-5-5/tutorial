from typing import List
from itertools import pairwise
class Solution:
    def countOperationsToEmptyArray(self, nums: List[int]) -> int:
        '''n(删除次数) + 移动次数
        关键在于移动次数
        如果是有序 1 2 3 4 则只需要删除4次, 无需移动(删除后的下一次移动免费)
        但如果无序, 则需要绕圈, 绕一圈需要移动 n-m 步, m = 已经删去的次数
        关键在于绕圈次数, 因为无序则必须绕圈
        例:2 4 1 3  n = 4
        1. 从元素 1 移动到元素 2, 由于 2 在 1 左侧, 说明必须走一整圈才能到 2, 
        减去删除 1 产生的免费移动, 移动次数为 n-1 = 4-1 = 3。
        2. 从元素 3 移动到元素 3, 由于 4 在 3 左侧, 说明必须再走一整圈才能到 4, 
        减去删除 2,3 产生的免费移动, 减去跳过的 1, 移动次数为 n - 3 = 4-3 = 1。
        总移动次数 3 + 1 = 4
        '''
        ans = n = len(nums)
        ids = sorted(range(n), key=lambda x:nums[x])

        for k, (pre, i) in enumerate(pairwise(ids), 1):
            if pre > i:
                ans += n - k

        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.countOperationsToEmptyArray([1,2,4,3]))