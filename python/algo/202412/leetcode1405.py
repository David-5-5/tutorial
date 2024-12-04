import heapq

# 贪心专题 相邻不同 证明/构造方案
class Solution:
    def longestDiverseString(self, a: int, b: int, c: int) -> str:
        # 自行解答，使用堆，优先使用数量最多的字符
        cnt = []
        if a : cnt.append((-a, 'a'))
        if b : cnt.append((-b, 'b'))
        if c : cnt.append((-c, 'c'))
        heapq.heapify(cnt)
        ans = []
        while cnt:
            count, ch = heapq.heappop(cnt)
            if len(ans) >= 2 and ans[-1] == ans[-2] == ch:
                if not cnt:
                    break
                else:
                    nxt_c, nxt_ch = heapq.heappop(cnt)
                    ans.append(nxt_ch)
                    if nxt_c + 1:
                        heapq.heappush(cnt, (nxt_c+1, nxt_ch))
                    ans.append(ch)
            else:
                ans.append(ch)
            if count + 1:
                heapq.heappush(cnt, (count+1, ch))
        return "".join(ans)
        

if __name__ == "__main__":
    sol = Solution()
    print(sol.longestDiverseString(7,1,0))