from typing import Counter
class Solution:
    def countPalindromicSubsequence(self, s: str) -> int:
        # key 'a'~'z', value: [l, r]
        # where l is leftest index and r is rightest index of key
        pal = {}
        for i, ch in enumerate(s):
            if ch not in pal.keys():
                pal[ch] = [i,-1]
            else:
                pal[ch][1] = i
        ans = 0

        for _, v in pal.items():
            if v[0]+1 < v[1]:
                # 计算 s[l+1:r]不同字母的个数 和 l,r组成三个字符回文的数量
                # where l = v[0], r = v[1]
                ans += len(Counter(s[v[0]+1:v[1]]))
        return ans

if __name__ == "__main__":
    sol = Solution()
    s = "aabca"
    print(sol.countPalindromicSubsequence(s))