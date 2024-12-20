from typing import List

# 周赛 375
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        # 自行解答，起初用滑动窗口，推导出公式后直接计算
        # 数量统计，不重不漏，从左到右枚举包含 k 个 mx
        # 前缀数量 * 后缀数量
        # 前缀数量： 最左端 mx 的下标 + 1 
        # 后缀数量： 右端下一个mx的下标 - 最右端 mx 的下标
        #   右端为最后一个mx，则len(nums) - 最右端 mx 的下标
        ans, mx, n = 0, max(nums), len(nums)

        pos = [i for i, v in enumerate(nums) if v==mx ]

        m = len(pos)
        for i in range(m-k+1):
            ans += (pos[i]+1) * ((pos[i+k] if i+k < m else n) - pos[i+k-1])

        return ans
