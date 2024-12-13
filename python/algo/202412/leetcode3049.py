from collections import defaultdict, deque
from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def earliestSecondToMarkIndices(self, nums: List[int], changeIndices: List[int]) -> int:
        n, m = len(nums), len(changeIndices)

        marks = 0       # 已标记数量
        zeros = set()   # 元素为 i， 其中 nums[i] == 0 
        
        left = []
        l_i = {}
        for i, v in sorted(enumerate(nums), key=lambda p:p[1]):
            if v == 0: zeros.add(i)
            else:
                inx = len(left)
                left.append(v)
                l_i[i] = inx

        mx_left = sum(left) + len(left)
        def inc_nums_cnt(inc:int):
            cnt = ss = 0
            for v in left:
                if v == 0:continue
                ss += v + 1
                if ss <= inc:cnt += 1
                else: break
            return cnt

        inc_cnt = 0
        mark_cnt = 0
        for t in range(m):
            x = changeIndices[t]-1

            if x in zeros or inc_cnt+1>=len(zeros) + mx_left :
                inc_cnt += 1
                mark_cnt = min(inc_cnt, len(zeros))
                if inc_cnt> mark_cnt:
                    mark_cnt += inc_nums_cnt(inc_cnt-mark_cnt)
            else:
                left[l_i[x]] = 0
                mark_cnt = min(inc_cnt, len(zeros))
                if inc_cnt > mark_cnt:
                    mark_cnt += inc_nums_cnt(inc_cnt-mark_cnt)
                zeros.add(x)
                mx_left -= nums[x] + 1
            
            if mark_cnt == n: return t+1

        if mark_cnt == n: return m
        else: return -1
            
    
    def earliestSecondToMarkIndices2(self, nums: List[int], changeIndices: List[int]) -> int:
        n, m = len(nums), len(changeIndices)

        marks = inc = 0       # 已标记数量
        zeros = set()   # 元素为 i， 其中 nums[i] == 0 
        q = deque()
        q_inc = {}
        for i, v in sorted(enumerate(nums), key=lambda p:p[1]):
            if v == 0: zeros.add(i)
        for inx in changeIndices:
            inx -= 1
            if nums[inx]!= 0 and inx not in q_inc:
                q.appendleft(inx)
                q_inc[inx] = 0
        
        for inx, v in enumerate(nums):
            if v != 0 and inx not in q_inc:
                q.appendleft(inx)
                q_inc[inx] = 0            
        
        for t in range(m):
            x = changeIndices[t]-1
            if x in zeros:
                if marks < len(zeros): marks += 1
                elif q:
                    last = q[0]
                    q_inc[last] += 1
                    if q_inc[last] == nums[last]:
                        zeros.add(last)
                        del q_inc[last]
                        q.popleft()
            else:
                q.pop()
                del q_inc[x]
                zeros.add(x)
            if marks == n: return t + 1
        if marks == n: return m
        else: return -1
            

if __name__ == "__main__":
    sol = Solution()
    nums, changeIndices = [0,0,1,2], [1,2,1,2,1,2,1,2]
    nums, changeIndices = [5,1,3,2,2,5], [3,2,2,3,1,1,3,4,2,3,4,2,5,6,5,3,6,5,3]

    print(sol.earliestSecondToMarkIndices(nums, changeIndices))
    print(sol.earliestSecondToMarkIndices2(nums, changeIndices))