# 周赛 341
class Solution:
    def addMinimum(self, word: str) -> int:
        exp, exi = "abc", 0

        ans = 0
        for ch in word:
            while ch != exp[exi]:
                ans += 1
                exi = (exi + 1) % 3
            exi = (exi + 1) % 3
        
        if word[-1] == 'a': ans += 2
        elif word[-1] == 'b': ans += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.addMinimum("b"))
