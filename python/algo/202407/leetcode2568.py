from typing import List


class Solution:
    def minImpossibleOR(self, nums: List[int]) -> int:
        # 从 2^0, 2^1, 2^2 开始遍历
        # 如果存在 2^0 2^1, 执行 | 运算 2 ^ 2 -1 以下的数都存在
        # 2^2 exist, 执行 | 运算 2 ^ 3 -1 以下的数都存在
        # 以此类推，2^k exist, 执行 | 运算 2^(k+1) -1 以下的数都存在
        s = set(nums)
        for i in range(32):
            if 1 << i not in s:
                return 1<<i

                        
if __name__ == "__main__":
    sol = Solution()
    nums = [5,3,2]
    print(sol.minImpossibleOR(nums)) 
    print(sol.minImpossibleOR2(nums))    