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


    def minimumIncompatibility2(self, nums: List[int], k: int) -> int:
        # 超时 递归出现大量冗余计算
        n = len(nums)
        cnt = n // k

        def traverse_submasks(mask:int, i:int) -> List[int]:
            arr = []
            submask = mask
            while True:
                if submask.bit_count() == i:
                    arr.append(submask)
                submask = (submask - 1) & mask
                if submask == mask:
                    break
            return arr

        @cache
        def dfs(state:int) -> int:
            if state.bit_count() == 0: return 0
            
            res = inf
            next = traverse_submasks(state, state.bit_count()-cnt)

            for nt in next:
                cur = state - nt
                if values[cur] < inf:
                    res = min(res, values[cur] + dfs(nt))
            return res
        
        values = defaultdict(int)
        masks = traverse_submasks((1<<n) - 1, cnt)
        for v in masks:
            ntset, mx, mn = set(), 0, inf

            for i in range(n):
                if v >> i & 1:
                    ntset.add(nums[i])
                    mx = max(mx, nums[i])
                    mn = min(mn, nums[i])
            if len(ntset) == v.bit_count():
                values[v] = mx - mn
            else:  values[v] = inf

        ans = dfs((1<<n) - 1)
        return ans if ans < inf else -1 

    def minimumIncompatibility3(self, nums: List[int], k: int) -> int:
        # 参考题解，基于 minimumIncompatibility2 二进制子集遍历技巧
        # 从小到大遍历，避免重复
        n = len(nums)
        cnt = n // k
        # 遍历所有子集
        values = {}
        for mask in range(1<<n):
            if mask.bit_count() != cnt: continue
            distinct = set()
            mx, mn = 0, 18  # nums[i] <= 16
            for i in range(n):
                if mask >> i & 1:
                    distinct.add(nums[i])
                    if mx < nums[i]:mx = nums[i]
                    if mn > nums[i]:mn = nums[i]
            if len(distinct) == mask.bit_count():
                values[mask] = mx-mn
        

        dp = [inf] * (1 << n)
        dp[0] = 0
        for mask in range(1<<n):
            if dp[mask] == inf: # 剪枝
                continue    
            # 状态转移
            # k nums[i], v: i 相同的值只取一个
            exclusive = {}  # 和 mask 不相交的位
            for i in range(n):
                if mask >> i & 1 == 0:
                    exclusive[nums[i]] = i
            ex_mask = 0
            if len(exclusive) < cnt: # 剪枝
                continue
            for v in exclusive.values():
                ex_mask |= 1 << v
            nxt = ex_mask
            while nxt:
                if nxt in values.keys():
                    dp[mask | nxt] = min(dp[mask|nxt], dp[mask]+ values[nxt])
                nxt = (nxt - 1) & ex_mask
        return dp[-1] if dp[-1]<inf else -1