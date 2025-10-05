# 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution:
    def queryString(self, s: str, n: int) -> bool:
        return all(bin(i)[2:] in s for i in range(1, n+1))