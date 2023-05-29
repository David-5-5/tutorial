class Solution:
    def kthSmallest(self, mat, k: int) -> int:
        rows = len(mat)

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
        
        def next(matrix):
            ret = []
            candi = []
            for i in range(rows):
                if mat[i]:
                    minV, maxV = minmax(matrix, i, mat[i][0])
                    candi.append((minV, maxV, i))
            candi.sort()
            right = 0
            if not ret and candi:
                _, right, inx = candi.pop(0)
                ret.append(inx)
            while candi:
                l, r, inx = candi.pop(0)
                if l < right:
                    ret.append(inx)
                    right = max(right, r)
            return ret

        target = [[] for _ in range(rows)]    
        # initial target, pop first elment of each row from mat
        # and push into corresponding row of target
        for i in range(rows):
            target[i].append(mat[i].pop(0))

        while count(target) < k:
            nrows = next(target)
            for row in nrows:
                target[row].append(mat[row].pop(0))
                while mat[row] and target[row][-1] == mat[row][0]:
                    target[row].append(mat[row].pop(0))
        
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
    mat, k = [[1,3,11],[2,4,6]], 5
    mat, k = [[1,10,10],[1,4,5],[2,3,6]], 7
    mat, k = [[1,10,10],[1,4,5],[2,3,6]], 14
    mat, k = [[4,6,7],[4,7,8],[5,8,10],[4,8,9]], 10
    print(sol.kthSmallest(mat, k))