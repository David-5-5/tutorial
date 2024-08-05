from collections import defaultdict
from math import inf
from typing import List

# 双周赛 87
class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        # 自行解答，性能较差 O(96 * N)
        cnt = defaultdict(list)
        
        # lowbit
        for i, v in enumerate(nums):
            for e in range(32):
                if v >> e & 1 == 1:
                    cnt[e].append(i)
        for e in range(32):
            cnt[e].append(-1)
        
        ans = []
        for i, v in enumerate(nums):
            mn = -1
            for e in range(32):
                if v >> e & 1 == 1:
                    if i > mn: mn = i
                    cnt[e].pop(0)
                elif cnt[e][0] > mn:
                    mn = cnt[e][0]
            if mn == -1: ans.append(1)
            else :ans.append(mn-i+1)

        return ans     

    def smallestSubarrays2(self, nums: List[int]) -> List[int]:
        # 自行解答，倒序一次遍历，这次好多了，不过应该还有优化空间
        bitlen = max(nums).bit_length() + 1 # 时间是固定 32 位的一半
        cnt = [-1] * bitlen  # 存储幂(数组下标)的最小值，即最左端位置
        n = len(nums)
        # lowbit
        ans = [1] * n
        for i in range(n-1,-1,-1):
            v = nums[i]
            mn = -1 # 查找所有幂的最大值(最右端)
            for e in range(bitlen):
                if v >> e & 1 == 1:
                    cnt[e] = i
                    if i > mn: mn = i
                elif cnt[e] > mn:
                    mn = cnt[e]
            if mn != -1:  ans[i] = mn-i+1

        return ans
    

    def smallestSubarrays3(self, nums: List[int]) -> List[int]:
        # 参考题解， 方法一
        ans = [1] * len(nums)

        for i, v in enumerate(nums):
            for j in range(i-1, -1, -1):
                if nums[j] | v == nums[j]:
                    break
                nums[j] |= v
                ans[j] = i -j + 1
        return ans

    def smallestSubarrays4(self, nums: List[int]) -> List[int]:
        # 参考题解，方法二：模板题
        # 对应于自行解答方案二，smallestSubarrays2 模板题将 ors 替换 cnt 数组的值
        ans = [1] * len(nums)
        ors = [] # ors 中的值从后遍历 nums 中值的异或值，越左的异或值越大 
        # 元素值 1, 异或值 2, 合并相同异或值的最右端下标

        for i in range(len(nums)-1, -1, -1):
            x = nums[i]
            k = 0
            ors.append([0, i])
            for v in ors:
                v[0] |= x
                if v[0] == ors[k][0]:
                    ors[k][1] = v[1]
                else:
                    k += 1
                    ors[k] = v
            del ors[k+1:]
            ans[i] = ors[0][1] - i + 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1,0,2,1,3]
    print(sol.smallestSubarrays2(nums))
    print(sol.smallestSubarrays4(nums))

