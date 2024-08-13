from typing import List

# 双周赛 82 参考题解
class Solution:
    def minSumSquareDiff(self, nums1: List[int], nums2: List[int], k1: int, k2: int) -> int:
        k = k1 + k2
        a = [abs(x-y) for x, y in zip(nums1, nums2)]
        a.sort(reverse=True)
        a.append(0)
        if sum(a) <= k: return 0
        
        ans = 0
        for v in a: ans += v * v

        c, h = 0, a[0]
        for v in a:
            if k == 0:break
            if h > v:
                if (h - v)*c <= k:
                    ans -= (h * h - v * v) * c
                    k -= (h - v)*c
                    h = v
                else:
                    h1, c1 = k // c, k % c 
                    ans -= (h*h - (h-h1)*(h-h1)) * (c-c1) + (h*h - (h-h1-1)*(h-h1-1)) * c1
                    k = 0
            c += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2, k1, k2 = [1,4,10,12], [5,8,6,9], 1, 1
    nums1, nums2, k1, k2 = [7,11,4,19,11,5,6,1,8], [4,7,6,16,12,9,10,2,10], 3, 6
    print(sol.minSumSquareDiff(nums1, nums2, k1, k2))