from typing import List

# 图论算法 三、最短路 3.2 全源最短路：Floyd 算法
class Solution:
    def checkIfPrerequisite(self, numCourses: int, prerequisites: List[List[int]], queries: List[List[int]]) -> List[bool]:
        # Floyd
        f = [[False] * numCourses for _ in range(numCourses)]

        for p in prerequisites:
            f[p[0]][p[1]] = True
        
        for k in range(numCourses):
            for i in range(numCourses):
                for j in range(numCourses):
                    f[i][j] |= f[i][k] & f[k][j]

        ans = []
        for q in queries:
            ans.append(f[q[0]][q[1]])
        
        return ans