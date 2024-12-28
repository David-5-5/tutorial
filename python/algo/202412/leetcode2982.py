from collections import defaultdict

# 周赛 378
class Solution:
    def maximumLength(self, s: str) -> int:
        cnt_d = defaultdict(list)
        
        s += 'A' # 哨兵

        cnt, prev = 1, s[0]
        for ch in s[1:]:
            if ch == prev:
                cnt += 1
            else:
                cnt_d[prev].append(cnt)
                cnt, prev = 1, ch
        
        ans = 0
        for l_cnt in cnt_d.values():
            l_cnt.sort(reverse = True)
            if len(l_cnt) >= 1:
                ans = max(ans, l_cnt[0]-2)
            if len(l_cnt) >= 2:
                ans = max(ans, min(l_cnt[0]-1, l_cnt[1]))
            if len(l_cnt) >= 3:
                ans = max(ans, min(l_cnt[0:3]))

        return -1 if ans == 0 else ans