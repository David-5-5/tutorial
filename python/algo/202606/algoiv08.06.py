from typing import List


class Solution:
    def hanota(self, A: List[int], B: List[int], C: List[int]) -> None:
        """
        Do not return anything, modify C in-place instead.
        """
        def dfs(l: int, a: List[int], b: List, c: List):
            if l == 1:
                c.append(a.pop())
            else:
                dfs(l-1, a, c, b)
                c.append(a.pop())
                dfs(l-1, b, a, c)

        dfs(len(A), A, B, C)