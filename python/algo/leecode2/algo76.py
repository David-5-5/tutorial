from collections import deque
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


if __name__ == "__main__":
    sol = Solution()
    s, t = "ADOBECODEBANC", "ABBC"
    print(sol.minWindow(s, t))