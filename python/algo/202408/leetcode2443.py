# 周赛 315
class Solution:
    def sumOfNumberAndReverse(self, num: int) -> bool:
        # return any(num == c + int(str(c)[::-1]) for c in range(num+1))
        for c in range(num+1):
            r, x = c, 0
            while c:
                x = x*10 + c % 10
                c = c // 10
            if r + x == num: return True
        return False    

