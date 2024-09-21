from typing import List

# 周赛 296
class Solution:
    def arrayChange(self, nums: List[int], operations: List[List[int]]) -> List[int]:
        # 自行解答
        transfer = {}
        for f, t in operations[::-1]: # 倒序
            if t in transfer.keys():
                transfer[f] = transfer[t]
                del transfer[f]
            else: transfer[f] = t

        for i, num in enumerate(nums):
            if num not in transfer:continue
            nums[i] = transfer[num]
        
        return nums


if __name__ == "__main__":
    sol = Solution()
    nums, operations = [1,2,4,6], [[1,3],[4,7],[6,1]]
    print(sol.arrayChange(nums, operations))