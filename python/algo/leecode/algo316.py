class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        ret = []
        n = len(s)
        for i in range(n):
            if ret and s[i] in ret:
                continue
            while ret and ret[-1] > s[i]:
                if s.find(ret[-1], i) != -1:
                    ret.pop(-1)
                else:
                    break
            ret.append(s[i])
        return ''.join(ret)

if __name__ == "__main__":
    sol = Solution()

    s = "bcabc"
    print(sol.removeDuplicateLetters(s))