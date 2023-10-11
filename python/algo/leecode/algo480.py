from bisect import bisect_right
class Solution:
    def medianSlidingWindow(self, nums, k: int) :
        '''
        Put the k element to window and sort, remove the first element
        and put the new element into window.
        use bisect_right to find and insert in sorted window
        '''
        if k == 1: return nums
        n = len(nums)

        result = []
        window = nums[0:k]
        window.sort()
        def appendMedian():
            if k % 2 == 0:
                result.append((window[k//2]+window[k//2-1])/2)
            else:
                result.append(window[k//2])
        appendMedian()
        for i in range(k, n):
            # Remove the element num[i-k]
            inx = bisect_right(window, nums[i-k])
            # The inx -1 should be the index of nums[i-k] in window
            window.pop(inx-1)
            # Add the element nums[i]
            inx = bisect_right(window, nums[i])
            window.insert(inx, nums[i])
            appendMedian()

        return result