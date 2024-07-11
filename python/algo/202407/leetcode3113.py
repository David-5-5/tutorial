from typing import List
# 自行解答，专题单调栈
class Solution:
    def numberOfSubarrays(self, nums: List[int]) -> int:
        ans = len(nums)
        st = []
        for v in nums:
            while st and st[-1][0] < v:
                _, cnt = st.pop()
                ans += (cnt+1) * (cnt-1) - (cnt+2) * (cnt-1) // 2 
            if not st or st[-1][0] > v: st.append([v,1])
            else: st[-1][1] += 1
        
        for _, cnt in st:
            ans += (cnt+1) * (cnt-1) - (cnt+2) * (cnt-1) // 2 

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1,4,3,3,2]
    print(sol.numberOfSubarrays(nums))        