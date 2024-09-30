import heapq
from string import ascii_lowercase
from typing import Counter

# 双周赛 126
class Solution:
    def minimizeStringValue(self, s: str) -> str:
        # 自行解答，用数组比较 n * 26
        cnt = [0] * 26
        ans = [''] * len(s)
        torep = []
        pos = []
        for i, ch in enumerate(s):
            if ch != '?':
                ans[i] = ch
                cnt[ord(ch)-ord('a')] += 1
        
        for i, ch in enumerate(s):
            if ch == '?':
                ch_ord, ch_cnt = 0, cnt[0]
                for x in range(1, 26):
                    if cnt[x] < ch_cnt:
                        ch_ord, ch_cnt = x, cnt[x]
                
                cnt[ch_ord] += 1
                torep.append(chr(ord('a')+ch_ord))
                pos.append(i)
        
        torep.sort()
        for i, p in enumerate(pos):
            ans[p] = torep[i]

        return "".join(ans)
    
    def minimizeStringValue2(self, s: str) -> str:
        # 自行解答，用堆比较 n * 26
        cnt = [0] * 26
        ans = [''] * len(s)
        for i, ch in enumerate(s):
            if ch != '?':
                ans[i] = ch
                cnt[ord(ch)-ord('a')] += 1
        
        pq = [(v, k) for k, v in enumerate(cnt)]
        heapq.heapify(pq)
        
        torep = []
        pos = []
        for i, ch in enumerate(s):
            if ch == '?':
                torep.append(chr(ord('a')+pq[0][1]))
                pos.append(i)
                heapq.heapreplace(pq, (pq[0][0]+1, pq[0][1]))
        
        torep.sort()
        for i, p in enumerate(pos):
            ans[p] = torep[i]

        return "".join(ans)
    
    def minimizeStringValue3(self, s: str) -> str:
        # 参考题解，代码优化
        cnt = Counter(s)
        pq = [(cnt[ch], ch) for ch in ascii_lowercase]
        heapq.heapify(pq)
        
        torep = []
        for _ in range(cnt['?']):
            torep.append(pq[0][1])
            heapq.heapreplace(pq, (pq[0][0]+1, pq[0][1]))
        
        s, j = list(s), 0

        torep.sort()
        for i in range(len(s)):
            if s[i] == '?':
                s[i] = torep[j]
                j += 1

        return "".join(s)
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.minimizeStringValue2("???"))

        