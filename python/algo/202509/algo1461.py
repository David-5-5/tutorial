# 滑动窗口与双指针 - 定长滑动窗口 1.3 其他（选做）
class Solution:
    def hasAllCodes(self, s: str, k: int) -> bool:
        # 自行解答
        if len(s) < k: return False
        codes = set()
        val = 0
        for i in range(k-1):
            val = (val << 1) + int(s[i])
        
        for i in range(k-1, len(s)):
            val = (val << 1) + int(s[i])
            codes.add(val)
            val &= (1 << (k-1)) - 1
        
        return len(codes) == 1 << k