from typing import List


class Solution:
    def sortTheStudents(self, score: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(score), len(score[0])

        kscore = [score[i][k] for i in range(m)]
        # 存储中间变量，无需多次生成
        sort_k = [(r, r_) for r, [r_, _] in enumerate(sorted(enumerate(kscore), key=lambda p: -p[1]))]

        ans = [[0] * n for _ in range(m)]

        for r, r_ in sort_k:
            for c in range(n):
                ans[r][c] = score[r_][c]
        
        return ans
