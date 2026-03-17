class Solution:
    def minAnagramLength(self, s: str) -> int:
        # 自行解答， for ... else
        n = len(s)

        for l in range(1, n):
            if n % l: continue

            first = sorted(s[0:l])

            for i in range(l, n, l) :
                other = sorted(s[i:i+l])
                
                if (other!=first): break
            else: return l
        return n
