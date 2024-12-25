from typing import List

# 离线算法
class Solution:
    def smallestTrimmedNumbers(self, nums: List[str], queries: List[List[int]]) -> List[int]:
        ans = [-1] * len(queries)
        idx = list(range(len(nums)))
        prev = 1
        for qi, (k, t) in sorted(enumerate(queries), key=lambda p:(p[1][1], p[1][0])):
            # if prev<=t:
            #     idx.sort(key=lambda i:nums[i][-t:]) # 多位排序
            #     prev = t
            while prev<=t:
                idx.sort(key=lambda i:nums[i][-prev]) # 一位一位排序
                prev += 1
            ans[qi] = idx[k-1]

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, queries = ["102","473","251","814"], [[1,1],[2,3],[4,2],[1,2]]
    print(sol.smallestTrimmedNumbers(nums, queries))