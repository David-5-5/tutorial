from typing import List

# 位运算 - 拆位 / 贡献法
class Solution:
    def largestCombination(self, candidates: List[int]) -> int:
        # 自行解答，数据范围 10 ^ 7 <= 1<< 24
        bit_cnt = [0] * 24
        for cand in candidates:
            for i in range(24):
                if (cand >> i) & 1:
                    bit_cnt[i] += 1
        
        return max(bit_cnt)  