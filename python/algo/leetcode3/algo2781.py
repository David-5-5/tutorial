from typing import List


class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        # use set for navie
        fs = set(forbidden)
        ans = 0
        l = 0
        for r in range(len(word)):
            # forbidden 最长10个字符，长度超过10个字符，肯定不会匹配
            # 从最靠近 r 开始匹配，提升效率
            for i in range(r, max(l-1,r-10),-1):
                if word[i:r+1] in fs:
                    l = i+1
                    break
            ans = max(ans, r - l + 1)
        return ans

if __name__ == "__main__":
    sol = Solution()
    word, forbidden = "aaaabaaacc", ["bcca","aaa","aabaa","baaac"]
    print(sol.longestValidSubstring(word, forbidden))