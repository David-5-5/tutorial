from collections import defaultdict

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def subsequencesWithMiddleMode(self, nums: list) -> int:
        # deepseek 生成
        MOD = 10**9 + 7
        
        def comb2(num: int) -> int:
            return num * (num - 1) // 2
        
        n = len(nums)
        # 计算所有可能的长度为5的子序列总数
        total = n * (n - 1) * (n - 2) * (n - 3) * (n - 4) // 120
        if n < 5:
            return 0
        
        # 初始化频率字典
        suf = defaultdict(int)
        for num in nums:
            suf[num] += 1
        pre = defaultdict(int)
        
        # 初始化统计变量
        cp = 0
        cs = 0
        for count in suf.values():
            cs += comb2(count)
        ps = 0
        p2s = 0
        ps2 = 0
        
        # 遍历数组，枚举每个位置作为中间元素
        for i in range(n - 2):
            x = nums[i]
            left_count = i  # 左边元素个数
            right_count = n - 1 - i  # 右边元素个数
            
            # 更新后缀频率
            suf[x] -= 1
            px = pre[x]  # x 在左边已出现的次数
            sx = suf[x]  # x 在右边剩余的次数
            
            # 更新组合统计量
            cs -= sx
            ps -= px
            p2s -= px * px
            ps2 -= (sx * 2 + 1) * px
            
            # 计算不满足条件的子序列数量
            term1 = comb2(left_count - px) * comb2(right_count - sx)
            term2 = (cp - comb2(px)) * sx * (right_count - sx)
            term3 = (cs - comb2(sx)) * px * (left_count - px)
            term4 = ((ps - px * sx) * (right_count - sx) - (ps2 - px * sx * sx)) * px
            term5 = ((ps - px * sx) * (left_count - px) - (p2s - px * px * sx)) * sx
            
            total -= (term1 + term2 + term3 + term4 + term5)
            
            # 更新前缀统计
            cp += px
            ps += sx
            ps2 += sx * sx
            p2s += (px * 2 + 1) * sx
            pre[x] += 1

        return total % MOD