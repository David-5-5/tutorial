from bisect import bisect_left
from typing import List

# 双周赛 126
class Solution:
    def unmarkedSumArray(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        # 自行解答
        n = len(nums)
        id_num = sorted(zip(nums, range(n)))

        n_sum = sum(nums)

        ans = []
        for i, k in queries:
            l = bisect_left(id_num, (nums[i], i))
            if l < len(id_num) and id_num[l] == (nums[i], i):
                id_num.pop(l)
                n_sum -= nums[i]
            for _ in range(k):
                if not id_num: break
                v, _ = id_num.pop(0)
                n_sum -= v
            ans.append(n_sum)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, queries = [1,2,2,1,2,3,1], [[1,2],[3,3],[4,2]]
    print(sol.unmarkedSumArray(nums, queries))


