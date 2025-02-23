from sortedcontainers import SortedDict
from bisect import bisect_left, bisect_right
class Solution:
    def maxEnvelopes(self, envelopes) -> int:
        '''
        TODO : Need improvement
        '''
        n = len(envelopes)
        envelopes.sort()
        cache = SortedDict()
        cache[1] = [(envelopes[0][1],envelopes[0][0])]
        for i in range(1, n):
            found = False
            for cnt in range(len(cache.keys()), 0, -1):
                if found: break
                inx = bisect_right(cache[cnt], (envelopes[i][1],envelopes[i][0]))
                if inx == 0: continue
                    
                for pos in range(inx):
                    if cache[cnt][pos][0] < envelopes[i][1] and cache[cnt][pos][1] < envelopes[i][0]:
                        if cnt+1 in cache.keys():
                            new_inx = bisect_right(cache[cnt+1], (envelopes[i][1],envelopes[i][0]))
                            cache[cnt+1].insert(new_inx, (envelopes[i][1],envelopes[i][0]))
                        else:
                            cache[cnt+1] = [(envelopes[i][1],envelopes[i][0])]
                        found = True
                        break

            if not found:
                new_inx = bisect_right(cache[1], (envelopes[i][1],envelopes[i][0]))
                cache[1].insert(new_inx, (envelopes[i][1],envelopes[i][0]))
        
        return len(cache)
        

    def maxEnvelopes2(self, envelopes) -> int:
        # 2025.2 复习，参考题解
        # 二维LIS 一维排序从低到高，
        # 另一维从高到低排序， 这是算法精妙的地方，按照要求，信封相套必须大于，
        # 而不是大于等于，第一维相同的情况下只会选择一个，这样在不需要重新比较第一维数据的情况下
        # 按照第二维 LIS 算法得到结果
        envelopes.sort(key = lambda p:(p[0],-p[1]))

        # 以下同 300
        dp = []
        for _, h in envelopes:
            if not dp or h > dp[-1]: dp.append(h)
            else:
                inx = bisect_left(dp, h)
                dp[inx] = min(h, dp[inx])
        
        return len(dp)



if __name__ == "__main__":
    sol = Solution()        
    envelopes = [[2,100],[3,200],[4,300],[5,500],[5,400],[5,250],[6,370],[6,360],[7,380]]
    envelopes = [[15,8],[2,20],[2,14],[4,17],[8,19],[8,9],[5,7],[11,19],[8,11],[13,11],[2,13],[11,19],[8,11],[13,11],[2,13],[11,19],[16,1],[18,13],[14,17],[18,19]]
    envelopes = [[6,10],[11,14],[6,1],[16,14],[13,2]]
    print(sol.maxEnvelopes(envelopes))