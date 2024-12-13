from collections import defaultdict
from itertools import accumulate


class Solution:
    def beautifulSubstrings(self, s: str, k: int) -> int:
        # 参考题意，自行解答
        # Hash 求两数之和 + 确定长度的同余式
        vowels = ['a', 'e', 'i', 'o', 'u']
        
        # 将元音及辅音替换为1, -1 则元音辅音的数量相等，presum[j]-presum[i] == 0
        # presum[j] 找相同值的 hash 数量
        nums = [1 if ch in vowels else -1 for ch in s]

        # 同时(元音数量 * 辅音数量) % k == 0  推导出 ==> ((j-i)/2)^2 % k == 0
        # 如果 k 不包含平方数 则 (j - i) % 2k == 0
        #     k 包含平平方数 则 (j - i) % 2k/v == 0, 其中 k % (v^2) == 0
        # 1000 以内最大的平方数为 31，从最大值查找包含的平方数
        def get_mod(v:int) -> int: 
            for div in range(31, 1, -1):
                if v % (div*div) == 0:
                    return v // div
            return v
        km = 2 * get_mod(k)
        presum = list(accumulate(nums, initial=0))

        ans = 0
        h = defaultdict(int)
        for i, v in enumerate(presum):
            ans += h[(i%km, v)]
            h[(i%km, v)] += 1
        
        return ans

        