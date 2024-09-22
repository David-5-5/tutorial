from typing import List

# 周赛 296
class Solution:
    def arrayChange(self, nums: List[int], operations: List[List[int]]) -> List[int]:
        # 自行解答
        transfer = {}
        # for f, t in operations[::-1]: # 倒序
        #     if t in transfer.keys():
        #         transfer[f] = transfer[t]
        #         del transfer[f]  # 删除可忽略
        #     else: transfer[f] = t

        # for i, num in enumerate(nums):
        #     if num not in transfer:continue
        #     nums[i] = transfer[num]
        
        # return nums

        # 参考题解，更 python 的写法
        for f, t in operations[::-1]: # 倒序
            transfer[f] = transfer.get(t, t)
        
        return [transfer.get(x, x) for x in nums]

if __name__ == "__main__":
    sol = Solution()
    nums, operations = [1,2,4,6], [[1,3],[4,7],[6,1]]
    print(sol.arrayChange(nums, operations))