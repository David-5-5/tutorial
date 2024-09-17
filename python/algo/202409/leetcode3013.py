import heapq
from typing import List

# 双周赛 122
class Solution:
    def minimumCost(self, nums: List[int], k: int, dist: int) -> int:
        # 参考题意，自行解答
        l, r, n = 1, dist + 1, len(nums)
        
        h = list(zip(nums[l:r+1], [i for i in range(l, r+1)]))
        heapq.heapify(h)

        ans = nums[0]
        kthd = {}
        kthpq = []
        for _ in range(k-1):
            v, inx = heapq.heappop(h)
            ans += v
            kthpq.append((-v,inx))
            kthd[inx] = v
        
        heapq.heapify(kthpq)
        
        l += 1
        r += 1
        mnans = ans
        while r < n:

            while h and h[0][1] < l:
                heapq.heappop(h)

            heapq.heappush(h, (nums[r], r))

            if l - 1 in kthd.keys():
                v, inx = heapq.heappop(h)
                ans += v - kthd[l-1]
                if ans < mnans: 
                    mnans = ans
                del kthd[l-1]
                kthd[inx] = v
                heapq.heappush(kthpq, (-v, inx))
            
            while kthpq and kthpq[0][1] < l:
                heapq.heappop(kthpq)

            if kthpq and h and -kthpq[0][0] > h[0][0]:
                v_g, inx_g = heapq.heappop(kthpq)
                v_l, inx_l = heapq.heappop(h)

                ans += v_l + v_g # v 是负的
                if ans < mnans:
                    mnans = ans
                del kthd[inx_g]
                kthd[inx_l] = v_l
                heapq.heappush(kthpq, (-v_l, inx_l))
                if inx_g >= l:heapq.heappush(h, (-v_g, inx_g)) # 调试了好久

            l += 1
            r += 1                            

        return mnans

if __name__ == "__main__":
    sol = Solution()
    nums, k, dist = [1,3,2,6,4,2], 3, 3
    nums, k, dist = [10,1,2,2,2,1], 4, 3
    nums, k, dist = [10,8,18,9], 3, 1
    nums, k, dist = [8821,326804,434637,102799,335315,304326,270140,165994,415080,405457,77362,477034,76540,202026,445600,433192,78994,353943,255325,144939,191962,475973,61423,161140,51284,484392,407939,35239,228103,213404,350957,443665,75636,72737,117410],24,27
    print(sol.minimumCost(nums, k, dist))