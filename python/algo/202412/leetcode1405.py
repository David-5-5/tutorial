class Solution:
    def longestDiverseString(self, a: int, b: int, c: int) -> str:
        cnt = [[a, 'a'], [b, 'b'], [c, 'c']]

        cnt.sort(reverse=True)
        odd_t = False
        if cnt[0][0] > cnt[1][0] + cnt[2][0] + 1:
            m = cnt[0][0] // 2 + cnt[0][0] % 2
            if m > cnt[1][0] + cnt[2][0] + 1:
                m = cnt[1][0] + cnt[2][0] + 1
            else:
                if cnt[0][0] % 2: odd_t = True
            cnt[0][0] = m
            cnt[0][1] += cnt[0][1]
        
        ans = [''] * (sum(l for l, _ in cnt))
        begin = 0
        for ch_c, ch in cnt:
            for i in range(ch_c):
                if odd_t and i + 1 == ch_c:
                    ans[begin] = ch[0]
                else: ans[begin] = ch
                begin += 2
                if begin >= len(ans):
                    begin = 1
                
        return "".join(ans)
            
if __name__ == "__main__":
    sol = Solution()
    print(sol.longestDiverseString(1,1,7))