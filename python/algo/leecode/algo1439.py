import heapq

class Solution:
    def kthSmallest(self, mat, k: int) -> int:
        '''
        看题解自行解答，小根堆
        '''
        merge = []
        f = mat.pop(0)
        while mat:
            g = mat.pop(0)
            for i in f:
                for j in g:
                    heapq.heappush(merge, i+j)
            f = []
            while len(f) < k and merge:
                f.append(heapq.heappop(merge))
            merge = []
        
        return f.pop(-1)


    def kthSmallest2(self, mat, k: int) -> int:
        '''
        官方题解，小根堆
        '''
        def merge(f, g, k: int) :
            if len(g) > len(f):
                return merge(g, f, k)
            
            q = [(f[0] + g[i], 0, i) for i in range(len(g))]
            heapq.heapify(q)

            ans = list()
            while k and q:
                entry = heapq.heappop(q)
                ans.append(entry[0])
                if entry[1] + 1 < len(f):
                    heapq.heappush(q, (f[entry[1] + 1] + g[entry[2]], entry[1] + 1, entry[2]))
                k -= 1
            
            return ans
        
        prev = mat[0]
        for i in range(1, len(mat)):
            prev = merge(prev, mat[i], k)
        return prev[k - 1]


    def kthSmallest3(self, mat, k: int) -> int:
        '''
        二分查找+双指针
        '''

if __name__ == "__main__":
    sol = Solution()
    # mat, k = [[1,3,11],[2,4,6]], 5
    # mat, k = [[1,10,10],[1,4,5],[2,3,6]], 7
    # mat, k = [[1,10,10],[1,4,5],[2,3,6]], 14
    # mat, k = [[4,6,7],[4,7,8],[5,8,10],[4,8,9]], 10
    mat, k = [[1,30,290,313,390,580,672],[103,486,565,698,798,821,916],[193,256,313,528,793,880,939],[131,161,483,535,549,570,889],[4,51,94,236,515,666,750],[55,65,163,681,681,724,870],[168,361,395,542,690,719,891],[264,285,312,337,449,704,912],[108,309,644,720,798,803,924],[26,79,303,545,747,891,948],[138,147,191,314,644,749,867],[178,245,261,329,650,741,819],[57,325,460,475,569,801,957],[262,302,316,318,439,793,825]], 160
    print(sol.kthSmallest2(mat, k))