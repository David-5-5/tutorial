from bisect import bisect_right
import heapq
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

    def medianSlidingWindow2(self, nums, k: int) :
        if k == 1: return nums
        odd = k % 2
        # max_pq 是滑动窗口中的低区值，用大顶堆(python只有小顶堆，大顶堆值取负)，min_pq 是滑动窗口中的高区值用小顶堆
        # 堆中数据的关系为： max(max_pq) <= min(min_pq)  (忽略大顶堆中值取负操作)
        # 1、初始化
        max_pq, min_pq = list(zip([-i for i in nums[0:k]], [inx for inx in range(k)])), []
        heapq.heapify(max_pq)

        for _ in range(k//2):
            v, inx = heapq.heappop(max_pq)
            min_pq.append((-v, inx))
        heapq.heapify(min_pq)

        # 维护低区值的额定值和每次窗口滑动，数据出入堆后实际值(堆中无效数据懒删除)，
        # 最终需要进行平衡操作，保持 CNT_MAX_PQ == cnt_max
        CNT_MAX_PQ = cnt_max = len(max_pq) 

        def lazy_delete(pq, l:int):
            while pq and pq[0][1] < l:
                heapq.heappop(pq)

        def transfer(pq_from, pq_to, l:int):
            lazy_delete(pq_from, l) # pass without this statement
            v_from, i_from = heapq.heappop(pq_from)
            heapq.heappush(pq_to, (-v_from, i_from))

        def get_median(l:int):
            lazy_delete(max_pq, l)
            lazy_delete(min_pq, l)            
            if odd: return -max_pq[0][0]
            else: return (-max_pq[0][0] + min_pq[0][0]) / 2
        
        ans = [get_median(0)]
        for r in range(k, len(nums)):
            l = r - k + 1
            # 出窗口数据
            out = l - 1
            if nums[out] < -max_pq[0][0] or out == max_pq[0][1]: # 如果值等于堆顶，out已经不在窗口中，为索引的最小值
                cnt_max -= 1 # out 在 max_pq

            # r 进窗口
            if (max_pq and nums[r] < -max_pq[0][0]) or not(min_pq and nums[r]>min_pq[0][0]):
                heapq.heappush(max_pq, (-nums[r], r))
                cnt_max += 1
            else: 
                heapq.heappush(min_pq, (nums[r], r))
            
            # Balance
            if cnt_max < CNT_MAX_PQ:
                transfer(min_pq, max_pq, l)
                cnt_max += 1
            elif cnt_max > CNT_MAX_PQ:
                transfer(max_pq, min_pq, l)
                cnt_max -= 1

            ans.append(get_median(l))

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,3,-1,-3,5,3,6,7], 3
    nums, k = [7,0,3,9,9,9,1,7,2,3], 6
    print(sol.medianSlidingWindow(nums, k))
    print(sol.medianSlidingWindow2(nums, k))