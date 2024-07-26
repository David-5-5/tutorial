from typing import List

# 双周赛 91 枚举/构造题目
class Solution:
    def splitMessage(self, message: str, limit: int) -> List[str]:
        n = len(message)

        line = cap = 0
        while True:
            line += 1
            if line < 10:
                tail = 5
            elif line < 100:
                if line == 10: cap -= 9
                tail = 7
            elif line < 1000:
                if line == 100: cap -= 99
                tail = 9
            elif line < 10000:
                if line == 1000: cap -= 999
                tail = 11

            cap += limit - tail
            
            if limit <= tail: return [] # 必须包含等于，tail = limit时，cap 不会继续增加
            if cap >= n: break

        res,inx = [], 0
        for i in range(1, line+1):
            tail = f"<{i}/{line}>"
            res.append(message[inx:limit-len(tail)+inx] + tail)
            inx += limit - len(tail)
        return res


if __name__ == "__main__":
    sol = Solution()
    message, limit = "this is really a very awesome message", 9
    print(sol.splitMessage(message, limit))
