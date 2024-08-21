# 双周赛 122
class Solution:
    def checkStrings(self, s1: str, s2: str) -> bool:
        s1_1 = sorted(s1[::2])
        s1_2 = sorted(s1[1::2])
        s2_1 = sorted(s2[::2])
        s2_2 = sorted(s2[1::2])

        return s1_1 == s2_1 and s1_2 == s2_2

if __name__ == "__main__":
    sol = Solution()
    s1,s2 = "abcdba", "cabdab"
    print(sol.checkStrings(s1,s2))