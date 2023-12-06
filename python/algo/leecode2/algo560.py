from typing import List
class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        res = 0
        n = len(nums)
        dict_pres = {}
        pres = 0
        for i in range(n):
            pres += nums[i]
            if pres == k:
                res += 1
            if pres-k in dict_pres.keys():
                res += dict_pres[pres-k]
            if pres in dict_pres.keys():
                dict_pres[pres] += 1
            else:
                dict_pres[pres] = 1
        return res        