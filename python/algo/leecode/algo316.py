class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        ret = []
        n = len(s)
        for i in range(n):
            if ret and s[i] in ret:
                continue
            # s.find 性能优化
            while ret and ret[-1] > s[i]:
                if s.find(ret[-1], i) != -1:
                    ret.pop(-1)
                else:
                    break
            ret.append(s[i])
        return ''.join(ret)

    def removeDuplicateLetters2(self, s: str) -> str:
        """
        Recommend
        """
        ret = []
        n = len(s)
        last = [-1] * 26

        for i in range(n):
            last[ord(s[i])-ord('a')] = i
    
        for i in range(n):
            if ret and s[i] in ret:
                continue
            while ret and ret[-1] > s[i]:
                if last[ord(ret[-1])-ord('a')] > i:
                    ret.pop(-1)
                else:
                    break
            ret.append(s[i])
        return ''.join(ret)


    def removeDuplicateLetters3(self, s: str) -> str:
        '''
        Customized find method
        '''
        ret = []
        n = len(s)
        def find(ch, i):
            for inx in range(i+1, n):
                if s[inx] == ch:
                    return inx
            return -1
        
        for i in range(n):
            if ret and s[i] in ret:
                continue
            # Use customized find instead of find of str
            while ret and ret[-1] > s[i]:
                if find(ret[-1], i) != -1:
                    ret.pop(-1)
                else:
                    break
            ret.append(s[i])
        return ''.join(ret)


if __name__ == "__main__":
    sol = Solution()

    s = "bcabc"
    print(sol.removeDuplicateLetters(s))