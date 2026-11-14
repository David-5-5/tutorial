class Solution:
    def smallestBalancedIndex(self, nums: list[int]) -> int:
        # 先计算后缀超时，乘数太大
        n = len(nums)     
        pres = [0] * (n + 1)
        for i in range(n):
            pres[i+1] = pres[i] + nums[i]
        
        suf = 1
        for i in range(n-1, -1, -1):
            if suf == pres[i]: return i
            elif suf > pres[i]: break

            suf *= nums[i]
        return -1
        
    def smallestBalancedIndex(self, nums: list[int]) -> int:
        # 双指针 
        n = len(nums)     
        i, pres, j, sufd = 0, 0, n-1, 1
        while i < j and sufd <= 10 ** 14:
            if pres < sufd:
                pres += nums[i]
                i += 1
            else:
                sufd *= nums[j]
                j -= 1

        if pres == sufd: return i
        else: return -1
