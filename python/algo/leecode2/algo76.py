from collections import Counter, deque
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        # Handle the target str
        m = len(t)
        tdict = {}
        for i in range(m):
            if t[i] not in tdict.keys():
                tdict[t[i]] = [1, 0, deque()]
            else:
                tdict[t[i]][0] += 1
        
        kcount = len(tdict.keys())
        minw = (-1, 1)
        begin = len(s)

        def findMinBegin():
            minB = len(s)
            for key in tdict.keys():
                minB = min(minB, tdict[key][2][0]) if len(tdict[key][2]) else minB
            return minB

        n = len(s)
        for i in range(n):
            if s[i] in tdict.keys():
                ch = s[i]
                begin = min(begin, i)
                if tdict[ch][0] > tdict[ch][1]:
                    tdict[ch][2].append(i)
                    tdict[ch][1] += 1
                    if tdict[ch][0] == tdict[ch][1]:
                        kcount -= 1
                        if kcount == 0:
                            minw = (begin, i)
                else:
                    '''tdict[s[i]][0] == tdict[s[i]][1] '''
                    rm = tdict[ch][2].popleft()
                    tdict[ch][2].append(i)
                    if rm == begin:
                        begin = findMinBegin()
                        if kcount == 0 and i - begin < minw[1]-minw[0]:
                            minw = (begin, i)
                            
        return s[minw[0]:minw[1]+1] if kcount == 0 else ""


    def minWindow2(self, s: str, t: str) -> str:
        # 滑动窗口
        td = Counter(t)
        sd = Counter()

        def contain() -> bool:
            for k in td.keys():
                if sd[k] < td[k]: return False

            return True

        l = start = 0
        end = len(s)
        found = False
        for r, v in enumerate(s):
            sd[v] += 1
            if not contain(): continue

            found = True
            while contain():
                sd[s[l]] -= 1
                l += 1
            if r - l + 2 < end - start: 
                start = l - 1 # l-1 就是满足条件的第一个字符位置
                end = start + r - l + 2
                
        return s[start:end] if found else ""

if __name__ == "__main__":
    sol = Solution()
    s, t = "ADOBECODEBANC", "ABC"
    print(sol.minWindow(s, t))
    print(sol.minWindow2(s, t))