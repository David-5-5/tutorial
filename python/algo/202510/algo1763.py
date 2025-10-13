# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
from collections import defaultdict

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def longestNiceSubstring(self, s: str) -> str:
        # 滑动窗口 非暴力做法 - 时间复杂度 O(26 * n)
        ans, ts = "", len(set(s))
        for t in range(1, ts+1):
            cnt = defaultdict(lambda:[0,0])
            # 用 less_cnt 的变量可以优化 判断cnt中values的值
            l = 0  # cnt 中少于k的数量
            for r, ch in enumerate(s):
                if  'a' <= ch  <= 'z':
                    cnt[ch][0] += 1
                else:
                    cnt[chr(ord(ch)-ord('A')+ord('a'))][1] += 1

                while len(cnt) > t:
                    if  'a' <= s[l] <= 'z':
                        key = s[l]
                        offset = 0
                    else:
                        key = chr(ord(s[l])-ord('A')+ord('a'))
                        offset = 1
                    cnt[key][offset] -= 1
                    if cnt[key][0] == 0 and cnt[key][1] == 0:
                        del cnt[key]
                    l += 1
            
                def satis() -> bool:
                    for v in cnt.values():
                        if v[0] == 0 or v[1] == 0: return False
                    return True

                if satis() and r-l+1 > len(ans):
                    ans = s[l:r+1]

        return ans

if __name__  == "__main__":
    print(Solution().longestNiceSubstring("YazaAay"))