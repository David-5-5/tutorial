class Solution:
    def findMedianSortedArrays(self, nums1, nums2) -> float:
        '''
        按照官方视频解答
        '''
        if len(nums1) > len(nums2):
            return self.findMedianSortedArrays(nums2, nums1)
        
        m = len(nums1)
        n = len(nums2)
        odd = (m + n) % 2
        totalLeft = (m + n + 1) // 2

        left = 0
        right = m
        count = 0
        while left < right:
            count += 1
            i = left + (right - left + 1) // 2
            j = totalLeft - i
            if nums1[i-1] > nums2[j]:
                right = i - 1
            else:
                left = i
        print(count)
        i = left
        j = totalLeft - i
        nums1LeftMax = nums1[i-1] if i else - float("inf")
        nums1RightMin = nums1[i] if i < m else float("inf")
        nums2LeftMax = nums2[j-1] if j else - float("inf")
        nums2RightMin = nums2[j] if j < n else float("inf")

        if odd:
            return max(nums1LeftMax, nums2LeftMax)
        else:
            return (max(nums1LeftMax, nums2LeftMax)+min(nums1RightMin, nums2RightMin))/2

    def findMedianSortedArrays3(self, nums1, nums2) -> float:
        if len(nums1) > len(nums2):
            return self.findMedianSortedArrays(nums2, nums1)
        
        m = len(nums1)
        n = len(nums2)
        odd = (m + n) % 2
        totalLeft = (m + n + 1) // 2

        left = 0
        right = m
        count = 0
        while left < right:
            count += 1
            i = left + (right - left) // 2
            j = totalLeft - i
            if nums2[j-1] > nums1[i]:
                left = i + 1
            elif i and nums1[i-1] > nums2[j]:
                '''
                相比官方视频, 增加条件判断, 更快的完成比较, 性能更高
                '''
                right = i
            else:
                # 将最后一次计算的中间值带出
                left = i
                break
        print(count)
        i = left
        j = totalLeft - i
        nums1LeftMax = nums1[i-1] if i else - float("inf")
        nums1RightMin = nums1[i] if i < m else float("inf")
        nums2LeftMax = nums2[j-1] if j else - float("inf")
        nums2RightMin = nums2[j] if j < n else float("inf")

        if odd:
            return max(nums1LeftMax, nums2LeftMax)
        else:
            return (max(nums1LeftMax, nums2LeftMax)+min(nums1RightMin, nums2RightMin))/2

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
    
    nums1 = [random.randint(-10000, 10000) for _ in  range(1000000)]
    nums2 = [random.randint(-10000, 10000) for _ in  range(1000000)]
    nums1.sort()
    nums2.sort()
    # nums1, nums2 = [3], [-2, -1]
    # nums1, nums2 = [1, 2], [3, 4]
    # nums1, nums2 = [1, 3], [2, 4]
    # nums1, nums2 = [1, 4], [2, 3]
    # nums1, nums2 = [2,2,2], [1,1,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3]
    # nums1, nums2 = [1,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5], [3,3,3]
    # nums1, nums2 = [5,6,7,9,10], [1,2,3,4,8]
    # nums1, nums2 = [1,2,3,4,8], [2,2,7,9,10]
    begin = datetime.now()
    ret1 = sol.findMedianSortedArrays(nums1, nums2)
    print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    ret2 = sol.findMedianSortedArrays3(nums1,nums2)
    print((datetime.now()- begin).total_seconds())
    if  ret1 != ret2:
        print(f'Wrong, Results of the {ret1} {ret2}')
    else:
        print(f'Right, Results of the {ret1}')