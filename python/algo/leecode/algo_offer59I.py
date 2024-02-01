import collections
class Solution:
    # 与主战 No 239相同 剑指分类取消了
    def maxSlidingWindow(self, nums , k: int) :
        n = len(nums)
        def slide(begin, x, curMax) -> int:
            slides = nums[begin:min(n, begin + x)]
            if len(slides) == 0: return 0
            max2 = max(slides)
            while max2 > curMax:
                inx = slides.index(max2)
                if inx > 0:
                    slides = slides[0:inx]
                    max2 = max(slides)
                else:
                    return 0
            return len(slides)

        cursor = k
        maxs = []
        window = nums[0:cursor]
        sl, inxMax = 0, 0
        while cursor <= n:
            if sl < inxMax:
                curMax = window[-1]
                inxMax = k - 1
            else:
                curMax = max(window)
                inxMax = window.index(curMax)

            sl = slide(cursor, inxMax, curMax)
            maxs = maxs + [curMax for _ in range(sl + 1)] 

            window = window[sl+1:k] + nums[cursor: cursor+sl+1]
            cursor += sl + 1

        return maxs


    def maxSlidingWindow2(self, nums , k: int) :
        import heapq
        n = len(nums)
        hq = []
        maxs = []
        
        # initial
        for i in range(k):
            heapq.heappush(hq, (-nums[i],i))
        
        for i in range(k, n + 1):
            val, index = hq[0]
            while not (index>=i-k and index < i):
                heapq.heappop(hq)
                val, index = hq[0]
            maxs.append(-val)
            if i < n : heapq.heappush(hq, (-nums[i],i))

        return maxs


    def maxSlidingWindow3(self, nums , k: int) :
        maxs = []
        deque = collections.deque()
        n = len(nums)
        for i in range(k):
            while deque and nums[deque[-1]] < nums[i]:
                deque.pop()
            
            deque.append(i)

        for i in range(k, n + 1):
            while not (deque[0]>=i-k and deque[0] < i):
                deque.popleft()
            maxs.append(nums[deque[0]])
            if i < n :
                while deque and nums[deque[-1]] < nums[i]:
                    deque.pop()
                deque.append(i)
        
        return maxs


if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,3,-1,-3,5,3,6,7], 3
    print(sol.maxSlidingWindow3(nums, k))
