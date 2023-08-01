import math
class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s)

        def compute(ch):
            ret = []
            inx = s.find(ch, 0)
            while inx != -1:
                cursor = inx + 1
                while cursor < n and s[cursor] == ch:
                    cursor += 1
                ret.append(math.factorial(n) // (math.factorial(n-cursor+inx)*math.factorial(cursor-inx)))
                inx = s.find(ch, cursor)
            if ret:
                return sum(ret) + 1 - len(ret)
            else:
                return 1
        ans1 = compute('D')
        ans2 = compute('I')
        return max(ans1, ans2)

if __name__ == "__main__":
    sol = Solution()
    s = "DIDI"
    print(sol.numPermsDISequence(s))