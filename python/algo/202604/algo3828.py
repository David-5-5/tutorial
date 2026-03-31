from typing import List

# 五、思维题 - 5.2 脑筋急转弯
class Solution:
    def finalElement(self, nums: List[int]) -> int:
        # 真是脑筋急转弯
        return max(nums[0], nums[-1])