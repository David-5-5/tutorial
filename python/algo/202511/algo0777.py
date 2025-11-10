# 滑动窗口与双指针 - 双序列双指针 - 4.1 双指针
class Solution:
    def canTransform(self, start: str, result: str) -> bool:
        # 同 2337
        n = len(start)
        i = j = 0

        while i < n or j < n:
            while i < n and start[i] == 'X':
                i += 1
            while j < n and result[j] == 'X':
                j += 1
            
            if j == n or i == n: break

            if (start[i] == result[j] == 'L' and j <= i ) or start[i] == result[j] == 'R' and j >= i:
                i += 1
                j += 1
            else:
                return False

        return i == j        