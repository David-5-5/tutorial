# 贪心专题 - 字典序最小/最大
from typing import List


class Solution:
    def monotoneIncreasingDigits(self, n: int) -> int:
        # 自行解答
        sn = [int(d) for d in str(n)]
        m = len(sn)

        ans = [0] * m
        ans[-1] = sn[-1]
        for i in range(m-2, -1, -1):
            if sn[i] <= ans[i+1]:
                ans[i] = sn[i]
            else:
                ans[i] = sn[i]-1
                for j in range(i+1, m):
                    ans[j] = 9
        
        return  sum(v*(10**(m-i-1)) for i, v in enumerate(ans))
    
    def monotoneIncreasingDigits2(self, n: int) -> int:
        # 贪心，参考题解思路
        sn = [int(d) for d in str(n)]
        m = len(sn)

        # 抽象出 check 方法，代码可读性更强
        def check(nums: List[int])->bool:
            return all(l<=r for l, r in zip(nums,nums[1:]))

        # n 本身就是递增序列
        if check(sn):return sum(v*(10**(m-i-1)) for i, v in enumerate(sn))

        # 从倒数第二位开始尝试，将位减少 1, 后续更新为 9
        for i in range(m-2, -1, -1):
            sn[i] -= 1
            # 冗余更新，不需要
            # for j in range(i+1, m):
            #     sn[j] = 9
            sn[i+1] = 9 # 不需要上述注释的循环语句，每次只更新后续数字为 9 即可
            if check(sn): return sum(v*(10**(m-i-1)) for i, v in enumerate(sn)) 

    def monotoneIncreasingDigits3(self, n: int) -> int:
        # 贪心，同 monotoneIncreasingDigits 换一种写法
        sn = [int(d) for d in str(n)]
        m = len(sn)

        # 抽象出 check 方法，代码可读性更强
        def check(nums: List[int])->bool:
            return all(l<=r for l, r in zip(nums,nums[1:]))

        # n 本身就是递增序列，直接返回
        if not check(sn):
            # 从倒数第二位开始尝试，将位减少 1, 后续更新为 9 
            for i in range(m-2, -1, -1):
                # 每次只更新后续数字为 9 即可
                sn[i], sn[i+1] = sn[i]- 1, 9
                if check(sn): break # 找到小于 n 最大的递增序列

        return sum(v*(10**(m-i-1)) for i, v in enumerate(sn))