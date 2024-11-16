# 周赛 400
class Solution:
    def clearStars(self, s: str) -> str:
        # 自行解答
        lst = [[] for _ in range(26)]
        sl = list(s)

        for i, ch in enumerate(s):
            if ch == "*":
                for j in range(26):
                    if lst[j]:
                        sl[lst[j].pop(-1)] = ''
                        break
                sl[i] = ''
            else:
                lst[ord(ch)-ord('a')].append(i)
                
        return "".join(sl)
