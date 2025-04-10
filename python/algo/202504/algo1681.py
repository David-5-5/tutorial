from cmath import inf
from functools import cache
from typing import List


class Solution:
    def combine(self, arr:List[int], k: int) -> List[List[int]]:
        n = len(arr)
        ans = []
        # path = []
        path = 0
        def dfs(i:int) -> None:
            nonlocal path
            # 剪枝，剩余的数字不够
            if path.bit_count() + n - i < k: return 

            if path.bit_count() == k:
                ans.append(path)
                return
            for j in range(i, n):
                # path.append(arr[j])
                path |= 1 << arr[j]
                dfs(j+1) # 选择 j 后续的值
                path -= 1 << arr[j]
        dfs(0)
        return ans
        
    def minimumIncompatibility(self, nums: List[int], k: int) -> int:
        n = len(nums)
        cnt = n // k

        @cache
        def dfs(state:int, l:int) -> int:
            if l == 0: return 0
            st = []
            for i in range(n):
                if state >> i & 1:
                    st.append(i)
            
            res = inf
            next = self.combine(st, cnt)
            # print(next)
            for nt in next:
                
                ntset = set()
                mx, mn, cur  = 0, inf, 0
                for i in range(n):
                    if nt >> i & 1:
                        ntset.add(nums[i])
                        mx = max(mx, nums[i])
                        mn = min(mn, nums[i])
                    # cur |= 1 << v
                if len(ntset) != nt.bit_count(): continue
                res = min(res, mx-mn + dfs(state-nt, l-1))
            return res
        ans = dfs((1<<n) - 1, k)
        return ans if ans < inf else -1