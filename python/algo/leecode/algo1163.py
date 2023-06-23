class Solution:
    def lastSubstring(self, s: str) -> str:
        ret = []
        for let in s:
            if not ret:
                ret.append(let)
            else:
                if ret[0] < let:
                    ret = [let]
                else:
                    ret.append(let)
        result = ''.join(ret)
        
        inx = ret.index(ret[0], 1) if ret[0] in ret[1:] else -1
        while inx != -1:
            result = max(result, ''.join(ret[inx:]))
            inx = ret.index(ret[0], inx+1) if ret[0] in ret[inx+1:] else -1
            
        return result
        

if __name__ == "__main__":
    sol = Solution()
    s = "abab"
    print(sol.lastSubstring(s))