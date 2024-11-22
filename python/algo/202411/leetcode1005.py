from math import inf
from typing import List

# 贪心专题
class Solution:
    def largestSumAfterKNegations(self, nums: List[int], k: int) -> int:
        # 使用桶排序，参考提示，自行解答

        bucket, bias = [0] * 201, 100
        for v in nums:
            bucket[v+bias] += 1
        
        for i in range(201):  #从小到大遍历
            if k == 0:break

            val, cnt = i - bias, bucket[i]
            if not cnt:continue
            if val < 0: # 越小负数尽量改为正数
                bucket[200-i] += min(cnt, k)
                bucket[i] -= min(cnt, k)
                k -= min(cnt, k)
            else: # 找到最小的非负数
                if val and k % 2: # 奇数情况下和非零情况下
                    bucket[200-i] += 1
                    bucket[i] -= 1
                k = 0
        return sum(c * (i-bias) for i, c in enumerate(bucket))
            

if __name__ == "__main__":
    sol = Solution()
    nums, k = [5,6,9,-3,3], 2
    print(sol.largestSumAfterKNegations(nums, k))