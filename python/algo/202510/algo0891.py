MOD = 10**9 + 7


# 数学算法 - 组合数学 - 2.5 贡献法
class Solution:
    def sumSubseqWidths(self, nums):
        n = len(nums)
        # 计算后缀中 <= 当前元素的数量
        partial = []
        suf_le_cnt = [0] * n
        for i in range(n-1, -1, -1):
            # 找到第一个大于nums[i]的位置（upper_bound）
            left, right = 0, len(partial)
            while left < right:
                mid = (left + right) // 2
                if partial[mid] > nums[i]:
                    right = mid
                else:
                    left = mid + 1
            suf_le_cnt[i] = left  # 小于等于nums[i]的元素个数
            # 插入当前元素到合适位置，保持partial有序
            partial.insert(left, nums[i])
        
        # 计算前缀中 < 当前元素的数量，并累加贡献
        partial.clear()
        ans = 0
        for i in range(n):
            # 找到第一个大于等于nums[i]的位置（lower_bound）
            left, right = 0, len(partial)
            while left < right:
                mid = (left + right) // 2
                if partial[mid] >= nums[i]:
                    right = mid
                else:
                    left = mid + 1
            pre_less = left  # 小于nums[i]的元素个数
            # 插入当前元素到合适位置，保持partial有序
            partial.insert(left, nums[i])
            
            # 计算前缀中大于当前元素的数量和后缀中大于当前元素的数量
            pre_gt = i - pre_less
            suf_great = (n - 1 - i) - suf_le_cnt[i]
            
            # 累加最大值贡献和最小值贡献（带模运算）
            ans += nums[i] * (pow(2, pre_less + suf_le_cnt[i], MOD)-pow(2,pre_gt + suf_great, MOD))
            ans %= MOD
        
        # 最终结果：(max_ans - min_ans) 可能为负，加MOD后再取模
        return ans
    
    def sumSubseqWidths2(self, nums):
        # 实际上，nums排序后，对于 nums[i] 的
        # - 前 i 个元素就是小于 nums[i] nums[i] 在 2^i 个子序列中贡献最大值
        # - 后 n-i-1 个元素就是大于 nums[i] 的数，在 2^(n-1-i) 中贡献最小值
        # 仔细分析上面自行完成的代码，按照前后缀分解的最后又合并的数量，说明这样情况
        # 因此上面代码冗余了
        n = len(nums)
        ans = 0
        nums.sort()
        for i, v in enumerate(nums):
            ans += v * (pow(2, i, MOD) - pow(2, n-1-i, MOD))
            ans %= MOD

        return ans