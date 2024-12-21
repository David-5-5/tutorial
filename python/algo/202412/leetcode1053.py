from typing import List

# 贪心专题 - 字典序最小/最大
class Solution:
    def prevPermOpt1(self, arr: List[int]) -> List[int]:
        # 自行解答，其中满足条件1，条件2及条件3，就可以找到小于 arr 的最大数
        n = len(arr)

        # suf 为从右往左遍历数组，每个数字出现的最右位置
        # 存在 j, i < j and nums[i] > nums[j]
        suf, j = {}, -1 
        # 条件1 从右往左遍历数组, 确保满足条件的数在最右边
        for i in range(n-1, -1, -1):
            for k in sorted(suf.keys(), reverse=True):
                # 条件2 从大到小，找到最大的 nums[j]
                if arr[i] > k:
                    j = suf[k]
                    break
            if j != -1:
                arr[i], arr[j] = arr[j], arr[i]
                break
            
            suf[arr[i]] = i # 条件3 增加或替换，确保交换最左边的值
        return arr