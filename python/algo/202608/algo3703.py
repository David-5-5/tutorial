from collections import deque

class Solution:
    def removeSubstring(self, s: str, k: int) -> str:
        # 使用双向队列，满足条件输出，性能较好 160ms，但代码结构复杂
        l, r = 0, 0
        que = deque()
        ans = ""
        for ch in s:
            if ch == '(':
                if r: 
                    que.append((l, r))
                    l, r = 0, 0
                l += 1                    
            else:
                r += 1
                if r > l:
                    que.append((l, r))
                    l, r = 0, 0
                    while que:
                        ql, qr = que.popleft()
                        ans += "(" * ql + ")" * qr
                elif r == k:
                    l -= k
                    r -= k
                    if l == 0 and que:
                        l, r = que.pop()
        if l: que.append((l, r))
        while que:
            ql, qr = que.popleft()
            ans += "(" * ql + ")" * qr
        return ans
