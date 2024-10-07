# 周赛 349
class Solution:
    def smallestString(self, s: str) -> str:
        # 自行解答
        l = r = 0
        inx = s.find('a')
        if inx == -1:
            l, r = 0, len(s)
        elif inx > 0:
            l , r = 0, inx
        else: # inx == 0
            l = inx + 1
            while l < len(s) and s[l] == 'a':
                l += 1
            if l == len(s): return s[0:-1] + 'z' # 全为 a 至少需要更改一个字符
            r = s.find('a', l)
            if r == -1: r = len(s)
        
        sl = list(s)
        
        for i in range(l, r):
            sl[i] = chr(ord(sl[i])-1)
        
        return "".join(sl)

if __name__ == "__main__":
    sol = Solution()
    print(sol.smallestString("aa"))