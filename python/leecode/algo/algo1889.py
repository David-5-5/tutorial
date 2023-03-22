class Solution:
    def minWastedSpace(self, packages, boxes) -> int:
        '''
        !!!!Time limit exceeded!!!!
        '''
        n = len(packages)
        m = len(boxes)

        mod = 10**9 + 7
        ret = [10**9 + 9] * m
        
        packages.sort(reverse=True)

        for k in range(m):
            boxes[k].sort(reverse=True)
            bl = len(boxes[k])
            p_inx, b_inx = 0, 1
            boxCur = boxes[k][0]
            if packages[p_inx] > boxCur:
                continue;
            while p_inx < n:
                while b_inx < bl and boxes[k][b_inx] >= packages[p_inx]:
                    boxCur = boxes[k][b_inx]
                    b_inx += 1
                ret[k] = ((boxCur - packages[p_inx]) if ret[k] == 10**9 + 9 else (ret[k] + boxCur - packages[p_inx])) % mod
                p_inx += 1

        ans = min(ret)
        return -1 if ans == 10**9 + 9 else ans

    
    def minWastedSpace2(self, packages, boxes) -> int:
        '''
        The official solution
        '''
        from itertools import accumulate
        from bisect import bisect_right
        mod = 10**9 + 7

        packages.sort()

        # pre = list(accumulate(packages, initial=0))
        pre = [0] + list(accumulate(packages))

        # 辅助函数，通过前缀和数组，得到数组 packages[left..right] 的和
        get = lambda left, right: pre[right+1] - pre[left]

        ans = float("inf")
        for box in boxes:
            box.sort()
            # If the size of the largest package is greater than the size 
            # of the largest box, it must not be satisfied, and skip directly
            if packages[-1] > box[-1]:
                continue
            
            # initial the pointer, point to the packages
            pt = 0
            # wasted space
            total = 0

            for cur in box:
                if cur < packages[pt]:
                    continue
                
                pt_next = bisect_right(packages, cur, pt) - 1
                total += (pt_next - pt + 1) * cur - get(pt, pt_next)
                pt = pt_next + 1
                if pt == len(packages):
                    break
            
            ans = min(ans, total)
        
        return -1 if ans == float("inf") else ans % mod

        
if __name__ == "__main__":
    sol = Solution()
    packages = [3,5,8,10,11,12]
    boxes = [[12],[11,9],[10,5,14]]
    print(sol.minWastedSpace2(packages, boxes))        
