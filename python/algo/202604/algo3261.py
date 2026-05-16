from typing import List

# 学习视频
class Solution:
    def countKConstraintSubstrings(self, s: str, k: int, queries: List[List[int]]) -> List[int]:
        n = len(s)

        # 滑动窗口计算 left 数组，即 [left[i], r]以r为最右元素的合法子串共 r - left[r] + 1
        left = [-1] * n
        l = cnt0 = cnt1 = 0
        for r, ch in enumerate(s):
            if ch == '1': cnt1 += 1
            else: cnt0 += 1
            while cnt0 > k and cnt1 > k:
                if s[l] == '1': cnt1 -= 1
                else: cnt0 -= 1
                l += 1
            left[r] = l
        
        #  计算以 r 为最右元素的合法子串的前缀和
        pres = [0] * (n + 1)
        for r, l in enumerate(left):
            pres[r+1] = pres[r] + (r-l+1)
        

        ans = []
        for q in queries:
            l, r = q[0], q[1]
            # 找出最小的 index 其 left[index] > q[0], 
            while l <= r:
                mid = (l + r) // 2
                if (left[mid]) <= q[0]:
                    l = mid + 1
                else: r = mid - 1
            # l 即为所求的 index 值
            # [q[0], l-1] 之间的left在边界或边界外， 计算 1 + 2 + ... l - q[0] + 1 的求和
            # [l, q[1]] 之间计算 pres[q[1]+1] - pres[l] 计算合法数的前缀和
            ans.append((l - q[0] + 1) * (l - q[0]) // 2 + pres[q[1]+1] - pres[l])

        return ans