import heapq
from typing import List

# 双周赛 122
# 使用 堆顶堆结构 + 滑动窗口 
# 超出滑动窗口范围的元素懒删除技巧，即pop时检查其索引是否在滑动窗口内
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

    def minimumCost2(self, nums: List[int], k: int, dist: int) -> int:
        # 基于以上实现，进行代码优化
        n = len(nums)

        win_pq = list(zip(nums[1:dist+2], [i for i in range(1,dist+2)]))
        heapq.heapify(win_pq)

        # Initialization
        kth_d, kth_pq = {}, []
        
        for _ in range(k-1):
            v, inx = heapq.heappop(win_pq)
            kth_d[inx] = v
            kth_pq.append((-v, inx))
        heapq.heapify(kth_pq)
        mnres = res = nums[0] + sum(kth_d.values())

        def lazy_delete(pq, l:int):
            while pq[0][1] < l: # 滑动窗口外，懒删除
                heapq.heappop(pq)

        def push_kth(t:tuple):
            kth_d[t[1]] = t[0]
            heapq.heappush(kth_pq, (-t[0], t[1]))
            
        for r in range(dist+2, n):
            l = r - dist
            heapq.heappush(win_pq, (nums[r], r))
            lazy_delete(win_pq, l)
            
            if (l-1) in kth_d.keys():
                v, inx = heapq.heappop(win_pq)
                res += v - kth_d[l-1]
                del kth_d[l-1]
                # push to kth
                push_kth((v, inx))
            else:
                lazy_delete(kth_pq, l)
                # exchange
                if -kth_pq[0][0] > win_pq[0][0]:
                    res += kth_pq[0][0] + win_pq[0][0]
                    
                    v_kth, inx_kth = heapq.heappop(kth_pq)
                    del kth_d[inx_kth]
                    heapq.heappush(win_pq, (-v_kth, inx_kth))

                    push_kth(heapq.heappop(win_pq))
            
            if mnres > res: mnres = res
        return mnres
            

if __name__ == "__main__":
    sol = Solution()
    nums, k, dist = [1,3,2,6,4,2], 3, 3
    nums, k, dist = [10,1,2,2,2,1], 4, 3
    nums, k, dist = [10,8,18,9], 3, 1
    nums, k, dist = [8821,326804,434637,102799,335315,304326,270140,165994,415080,405457,77362,477034,76540,202026,445600,433192,78994,353943,255325,144939,191962,475973,61423,161140,51284,484392,407939,35239,228103,213404,350957,443665,75636,72737,117410],24,27
    print(sol.minimumCost(nums, k, dist))
    print(sol.minimumCost2(nums, k, dist))