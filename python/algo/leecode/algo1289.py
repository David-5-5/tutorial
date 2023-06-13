import heapq

class Solution:
    def minFallingPathSum(self, grid) -> int:
        '''
        代码结合1439的最小根算法, 应可以优化
        '''
        if len(grid) == 1: return grid[0][0]

        def merge(f, g, k):
            merge = []
            for i in f:
                for j in g:
                    if i[1] != j[1]:
                        heapq.heappush(merge, (i[0]+j[0], j[1]))
            ret = []
            while len(ret) < k and merge:
                e = heapq.heappop(merge)
                if not ret:
                    ret.append(e)
                elif ret[0][1] != e[1]:
                    ret.append(e)
            return ret
            

        prev = [(q,qi) for qi, q in sorted(enumerate(grid[0]), key=lambda p:p[1])]
        prev = prev[0:2]
        for i in range(1, len(grid)):
            cur = [(q,qi) for qi, q in sorted(enumerate(grid[i]), key=lambda p:p[1])]
            prev = merge(prev ,cur, 2)

        return prev[0][0]

if __name__ == "__main__":
    sol = Solution()
    # arr = [[1,2,3],[4,5,6],[7,8,9]]
    arr = [[-37,51,-36,34,-22],[82,4,30,14,38],[-68,-52,-92,65,-85],[-49,-3,-77,8,-19],[-60,-71,-21,-62,-73]]
    print(sol.minFallingPathSum(arr))
