class Solution:
    def maximumValue(self, n: int, s: int, m: int) -> int:
        el, ol = (n+1)//2, n // 2
        return max(s + (m-1) * (el-1), s+m + (m-1)*(ol-1) if ol else 0)