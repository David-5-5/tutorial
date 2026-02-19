class Solution:
    def divide(self, a: int, b: int) -> int:
        # 同主站 29 一点都不简单
        INT_MX, INT_MN = 2**31-1, -2**31
        if a == INT_MN:
            if b == -1: return INT_MX # 不能溢出
            if b == 1: return INT_MN
        
        neg = False
        if a > 0 and b < 0 or a <0 and b > 0:
            neg = True

        if a < 0: a = -a
        if b < 0: b = -b
        que, x = [b], b

        while x <= a-x:
            x += x
            que.append(x)
        
        ans = 0
        for i in range(len(que)-1, -1, -1):
            if que[i] <= a:
                ans += (1<<i)
                a -= que[i]
        
        return -ans if neg else ans