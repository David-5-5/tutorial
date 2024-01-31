from typing import List
class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        n = len(nums)
        begin, lastMin, lastMax = 0, -1, -1
        # 记录最小上下界区间(i,j), 其中nums[i]= minK/maxK, nums[j]=maxK/minK
        # 若 minK ！= maxK，则 nums[i] != nums[j]
        # 多个上下界区间满足：
        # 1. distincts[k][0] < distincts[k+1][0]
        # 2. distincts[k][0] < distincts[k][1], minK != maxK
        # 3. distincts[k][0] == distincts[k][1], minK == maxK
        # 不同的上下界区间可能存在重叠, 例如：
        # - distincts[k][0] < distincts[k+1][0] < distincts[k][1] < distincts[k+1][1]
        # 但不存在两个区间完全包含, 例如：
        # - distincts[k][0] < distincts[k+1][0] < distincts[k+1][1] <= distincts[k][1]
        distincts = []

        ans = 0

        def count(begin, end):
            if not distincts:
                return 0
            ret = 0
            while distincts:
                left, right = distincts.pop(0)
                # 当前[left, right],前缀和后缀字符，进行组合，形成子数组
                # 计数方法 (前缀字符数量 + 1) * (后续子数组数量)
                ret += (left - begin + 1) * (end + 1 - right)
                begin = left + 1
            return ret

        for i in range(n):
            # nums[i] 在值域[minK, maxK] 之外，对上下界的进行计数
            if nums[i] < minK or nums[i] > maxK:
                ans += count(begin, i-1)
                begin, lastMin, lastMax = i+1, -1, -1
            if nums[i] == minK: # 设置下界的索引
                lastMin = i
            if nums[i] == maxK: # 设置上界的索引
                lastMax = i
            if lastMin != -1 and lastMax != -1: # 存在上下界的情况
                left = min(lastMin, lastMax) # 设置区间的最小索引
                right = max(lastMin, lastMax) # 设置区间的最大索引
                if not distincts:
                    distincts.append((left, right))
                elif distincts[-1][0] != left: # 避免重复及包含的区间
                    distincts.append((left, right))
        
        if distincts:
            ans += count(begin, n-1)
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, minK, maxK = [1,3,5,2,7,5], 1, 5
    # nums, minK, maxK = [1,3,5,2,1,5], 1, 5
    # nums, minK, maxK = [1,1,1,1], 1, 1
    # nums, minK, maxK = [1,1,5,2,1,5], 1, 5
    # nums, minK, maxK = [1,1,5,2,5,1], 1, 5
    print(sol.countSubarrays(nums, minK, maxK))