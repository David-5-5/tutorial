class Solution:
    def findMedianSortedArrays(self, nums1, nums2) -> float:
        from bisect import bisect_right
        n1, n2 = len(nums1), len(nums2)
        odd = (n1 + n2) % 2
        
        expect = (n1 + n2) // 2 - (1-odd)
        l1, r1, l2, r2 = 0, n1, 0, n2
        m1 = n1 // 2
        m2 = n2 // 2
        if n1 == 0 : return nums2[m2] if odd else (nums2[m2 - 1] + nums2[m2])/ 2
        if n2 == 0 : return nums1[m1] if odd else (nums1[m1 - 1] + nums1[m1])/ 2
    
        while m1 + m2 != expect:
            if nums1[m1] == nums2[m2]:
                return nums1[m1]
            elif nums1[m1] < nums2[m2]:
                l1 = m1
                r1 = bisect_right(nums1, nums2[m2], lo=m1, hi=r1)
                l2 = bisect_right(nums2, nums1[m1], lo=l2, hi=m2)
                r2 = m2
                m1 = (l1 + r1) // 2
                m2 = m2 -1 if m2 == (l2 + r2) // 2 else (l2 + r2) // 2
            else:
                l1 = bisect_right(nums1, nums2[m2], lo=l1, hi=m1)
                r1 = m1
                l2 = m2
                r2 = bisect_right(nums2, nums1[m1], lo=m2, hi=r2)
                m1 = m1 -1 if m1 == (l1 + r1) // 2 else (l1 + r1) // 2
                m2 = (l2 + r2) // 2
        
        return min(nums1[m1],nums2[m2]) if odd else (nums1[m1]+nums2[m2]) / 2

    def findMedianSortedArrays2(self, nums1, nums2) -> float:
        nums1.extend(nums2)
        nums1.sort()
        m = len(nums1) // 2
        odd = len(nums1) % 2
        return nums1[m] if odd else (nums1[m-1]+nums1[m]) / 2

if __name__ == "__main__":
    sol = Solution()
    
    from datetime import datetime
    import random
    
    # nums1 = [random.randint(-10000, 10000) for _ in  range(1000000)]
    # nums2 = [random.randint(-10000, 10000) for _ in  range(1000000)]
    # nums1.sort()
    # nums2.sort()
    #nums1, nums2 = [2,2,2], [2]
    nums1, nums2 = [1,2,3,4,8], [5,6,7,9,10]
    begin = datetime.now()
    ret1 = sol.findMedianSortedArrays(nums1, nums2)
    print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    ret2 = sol.findMedianSortedArrays2(nums1,nums2)
    print((datetime.now()- begin).total_seconds())
    if  ret1 != ret2:
        print("Wrong")