from cmath import inf
from collections import defaultdict


class Solution:
    def longestBalanced(self, s: str) -> int:
        # 自行解答，应该有更优雅的实现
        ans = 0
        # 本题仅有 abc 三个字符，26 个小写字母的情况，会超时
        for mask in range(1, 8):    # 枚举字符的组合 a b c ab ac bc abc
            cnt = [0] * 3
            prev = defaultdict(int)
            prev = {0:-1}
            for i, ch in enumerate(s):
                d = ord(ch) - ord('a')
                if (mask >> d) & 1 == 0:
                    cnt = [0] * 3   # reset
                    prev = {0:i}
                    continue
                else: cnt[d] += 1

                mn, key = inf, 0
                for j in range(3):
                    if (mask >> j) & 1: mn = min(mn, cnt[j])
                for j in range(3):
                    if (mask >> j) & 1:
                        key |= (cnt[j] - mn) << (j * 18)
                if key in prev:
                    ans = max(ans, i - prev[key])
                else: prev[key] = i
        return ans

if __name__ == "__main__":
    
    print(Solution().longestBalanced("acaaa"))
  