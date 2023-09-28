import heapq
class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits, capital) -> int:
        # 获取满足资产条件 <= w 的项目，加入优先列表中，优先获取最大利润的项目，
        # 保证最终的项目利润最大化
        sort_cap = [(q,qi) for qi, q in sorted(enumerate(capital), key=lambda p:p[1])]
        cur = 0
        prof = []
        trade = k

        # 初始化最初的项目
        while cur < len(sort_cap) and sort_cap[cur][0] <= w:
            heapq.heappush(prof, -profits[sort_cap[cur][1]])
            cur += 1

        while trade and prof:
            if prof:
                w -= heapq.heappop(prof)
                trade -= 1
            # 每次资本增加后，检查新的满足资产要求的项目，并加入优先队列
            while cur < len(sort_cap) and sort_cap[cur][0] <= w:
                heapq.heappush(prof, -profits[sort_cap[cur][1]])
                cur += 1
        
        return w

if __name__ == "__main__":
    sol = Solution()
    k, w, profits, capital = 1, 0, [1,2,3], [1,1,2]

    print(sol.findMaximizedCapital(k, w, profits, capital))
        