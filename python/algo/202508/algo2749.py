# 位运算 - 思维题 - 贪心、脑筋急转弯等
class Solution:
    def makeTheIntegerZero(self, num1: int, num2: int) -> int:
        # 自行解答
        cnt = 0
        while num1 > num2:
            cnt += 1
            num1 -= num2
            if num1.bit_count() <= cnt:
                print(num1)
                if num1 > cnt-num1.bit_count():return cnt
                else: return -1

        return -1