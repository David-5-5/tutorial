class Solution:
    def kthSmallest(self, mat, k: int) -> int:
        rows = len(mat)
        limit = 20000

        def count(matrix):
            result = 1
            for i in range(rows):
                result *= len(matrix[i])
            return result

        def minmax(matrix, row, value):
            minV, maxV = value, value
            for i in range(rows):
                if i != row:
                    minV += matrix[i][0]
                    maxV += matrix[i][-1]
            return minV, maxV
        
        target = [[] for _ in range(rows)]    
        def findMinimal():
            candi = []
            for i in range(rows):
                if mat[i]:
                    minV, maxV = minmax(target, i, mat[i][0])
                    candi.append((minV, maxV, i))
            candi.sort()
            _, right, inx = candi.pop(0)
            target[inx].append(mat[inx].pop(0))
            while mat[inx] and target[inx][-1] == mat[inx][0]:
                target[inx].append(mat[inx].pop(0))
            
            return right
        
        def findLessThanRight(right):
            #  if count(matrix) > limit: return
            candi = []
            for i in range(rows):
                if mat[i]:
                    minV, maxV = minmax(target, i, mat[i][0])
                    candi.append((minV, maxV, i))
            candi.sort()
            
            found = False
            while candi:
                l, r, inx = candi.pop(0)
                if l <= right:
                    found = True
                    target[inx].append(mat[inx].pop(0))
                    right = max(right, r)
            
            if found: 
                findLessThanRight(right)
            return

        # initial target, pop first elment of each row from mat
        # and push into corresponding row of target
        for i in range(rows):
            target[i].append(mat[i].pop(0))

        while count(target) < k:
            right = findMinimal()
            findLessThanRight(right)
        
        ret = 0
        if k == 1:
            for i in range(rows):
                ret += target[i][0]
            return ret
        elif k == count(target):
            for i in range(rows):
                ret += target[i][-1]
            return ret

        combi = target.pop(0)
        while target:
            factor1 = combi.copy()
            factor2 = target.pop(0)
            combi = []
            for i in range(len(factor1)):
                for j in range(len(factor2)):
                    combi.append(factor1[i]+factor2[j])
        combi.sort()
        return combi[k-1]

if __name__ == "__main__":
    sol = Solution()
    # mat, k = [[1,3,11],[2,4,6]], 5
    # mat, k = [[1,10,10],[1,4,5],[2,3,6]], 7
    # mat, k = [[1,10,10],[1,4,5],[2,3,6]], 14
    # mat, k = [[4,6,7],[4,7,8],[5,8,10],[4,8,9]], 10
    mat, k = [[1,30,290,313,390,580,672],[103,486,565,698,798,821,916],[193,256,313,528,793,880,939],[131,161,483,535,549,570,889],[4,51,94,236,515,666,750],[55,65,163,681,681,724,870],[168,361,395,542,690,719,891],[264,285,312,337,449,704,912],[108,309,644,720,798,803,924],[26,79,303,545,747,891,948],[138,147,191,314,644,749,867],[178,245,261,329,650,741,819],[57,325,460,475,569,801,957],[262,302,316,318,439,793,825]], 160
    print(sol.kthSmallest(mat, k))