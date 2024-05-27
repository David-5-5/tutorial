from typing import List
class Solution:
    # 连通图，每对情侣为一个节点，如果一对沙发是不同的情侣，表示节点之间存在连通
    # 这样最少移动次数就是每个连通分量的节点数量 - 1
    # 注：如果 每个情侣都在都是相邻的，则存在 N 个连通子图
    def minSwapsCouples(self, row: List[int]) -> int:
        n = len(row) // 2
        conn = [-1] * n

        def find(x:int) -> int:
            if conn[x] < 0:
                return x
            else:
                conn[x] = find(conn[x])
                return conn[x]
        
        def union(x:int, y:int):
            '''
            union the adt and return the position
            '''
            root1, root2 = find(x), find(y)
            if root1 == root2: return

            count = conn[root1]
            conn[root1] = root2
            conn[root2] += count

            
        for i in range(n):
            if row[2*i] // 2 != row[2*i+1] // 2:
                union(row[2*i] // 2, row[2*i+1] // 2)

        res = 0
        for count in conn:
            if count < 0:
                res += abs(count) - 1

        return res

    # Greedy algorithm
    # If it not a couples, find the couple
    def minSwapsCouples2(self, row: List[int]) -> int:
        n = len(row) // 2
        res = 0
        for i in range(n):
            couple = row[2*i] ^ 1
            if couple != row[2*i+1]:
                res += 1
                inx = row.index(couple, 2*i+1)
                row[inx] = row[2*i+1]
        return res

if __name__ == "__main__":
    sol = Solution()
    row = [2,0,5,4,3,1]
    print(sol.minSwapsCouples2(row))