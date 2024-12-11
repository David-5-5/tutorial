from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def earliestSecondToMarkIndices(self, nums: List[int], changeIndices: List[int]) -> int:
        n, m = len(nums), len(changeIndices)

        # marks = 0       # 已标记数量
        zeros = set()   # 元素为 i， 其中 nums[i] == 0 
        
        n_sum = sum(nums)
        for i, v in sorted(enumerate(nums), key=lambda p:p[1]):
            if v == 0: zeros.add(i)
        
        inc_cnt = 0
        mark_cnt = 0
        for t in range(m):
            if mark_cnt == n: return t
            x = changeIndices[t]-1
            if x in zeros:
                if mark_cnt < len(zeros) or n_sum <= inc_cnt:
                    mark_cnt += 1
                else: inc_cnt += 1
            else:
                inc_cnt += nums[x]
                zeros.add(x)

        if mark_cnt == n: return m
        else: return -1
    

if __name__ == "__main__":
    sol = Solution()
    nums, changeIndices = [0,0,1,2], [1,2,1,2,1,2,1,2]
    nums, changeIndices = [2,0,1], [2,2,1,1]

    print(sol.earliestSecondToMarkIndices(nums, changeIndices))