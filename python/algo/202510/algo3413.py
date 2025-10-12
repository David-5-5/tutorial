from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        # 自行解答 - 类似于2271 左右对齐 两次遍历

        def count(coins: List[List[int]]) -> int:
            ans = l = in_win = 0
            cl, cr = coins[0][0], coins[0][0]+k-1, 
            for _, [li, ri, ci] in enumerate(coins):
                in_win += (ri - li + 1) * ci
                cr = max(cr, ri)
                cl = cr - k + 1
                while coins[l][1] < cl:
                    in_win -= (coins[l][1] - coins[l][0] + 1) * coins[l][2]
                    l += 1
                # 最左coin部分覆盖
                uncover = max(cl - coins[l][0], 0)
                ans = max(ans, in_win - uncover * coins[l][2]) 
            return ans                     
        
        coins.sort()
        left = count(coins)
        coins.reverse()
        for t in coins:
            t[0], t[1] = -t[1], -t[0]
        right = count(coins)
        return max(left, right)