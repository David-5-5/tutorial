from cmath import inf
from collections import defaultdict, deque
from itertools import accumulate
from typing import List


class Solution:
    def findMaximumLength(self, nums: List[int]) -> int:
        n = len(nums)
        q = deque()
        q.append((0,0,0))
        presum = list(accumulate(nums, initial=0))
        for i in range(1, n+1):
            while len(q) > 1 and presum[q[1][2]] + q[1][1] <= presum[i]:
                q.popleft()
            
            cnt ,last = q[0][0]+1, presum[i]-presum[q[0][2]]

            while q and presum[q[-1][2]] + q[-1][1] >= presum[i] + last:
                 q.pop()

            q.append((cnt ,last, i))
        
        return q[-1][0]

    def count(self, s:str) -> int:
        mod = 72
        cur = defaultdict(int)
        next = defaultdict(int)
        ans = 0
        for ch in s:
            d = int(ch)
            
            if d == 0: ans += 1
            else: next[d] += 1
            
            for key, value in cur.items():
                new_k = (key * 10 + d) % mod
                if new_k == 0: ans += value
                next[new_k] += value
            
            cur = next
            next = defaultdict(int)
        return ans
        
    def count2(self, s:str) -> int:
        mod = 72
        n = len(s)
        ans = s.count('0')
        for i in range(n-1):
            if s[i] == '0':continue
            for j in range(i+1, n+1):
                if int(s[i:j]) % mod == 0: 
                    ans += 1
        return ans

if __name__ == '__main__':
    sol = Solution()
    
    nums = [279,641,864,511,317,169,848,277]
    # nums = [5,2,2,2,4,9,10]
    # nums = [1,2,3,4]
    print(sol.findMaximumLength(nums))
    print(sol.count("74444444444440000000000000000000044444333333333000000000000000000000000000003333333333332222222222222222222999999999999999999988888888888888"))
    print(sol.count2("74444444444440000000000000000000044444333333333000000000000000000000000000003333333333332222222222222222222999999999999999999988888888888888"))



def count(s:str, target:int) -> int:
    mod = 1000000007
    cur = defaultdict(int)
    next = defaultdict(int)
    ans = 0
    for ch in s:
        d = int(ch)
        
        if d == target: ans += 1
        next[d] += 1
        
        for key, value in cur.items():
            new_k = (key * 10 + d) % mod
            if new_k == target: ans += value
            next[new_k] += value
        
        cur = next
        next = defaultdict(int)
    return ans

s = input().strip()
cnt = int(input().strip())
for _ in range(cnt):
    t = int(input().strip())
    print(count(s, t))
