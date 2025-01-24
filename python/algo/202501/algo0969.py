from typing import List

# 贪心专题 - 构造题
class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:   
        def get_index(nums: List[int], val:int) -> int:
            for i, v in enumerate(nums):
                if v == val: return i
        
        ans = []
        while len(arr) > 1:
            n = len(arr)
            inx = get_index(arr, n)
            if inx + 1 != n:
                ans.extend([inx+1, n])
                arr = arr[inx+1:][::-1] + arr[:inx]
            else:
                arr = arr[:inx]
        return ans
