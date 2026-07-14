from functools import cache
from typing import List


class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        n = len(expression)

        @cache
        def dfs(l: int, r: int) -> List[int]:
            try:
                val = int(expression[l: r+1])
                return [val]
            except ValueError:
                pass
            
            res = []
            for i, ch in enumerate(expression[l: r+1]):
                if ch == '+':
                    for l_val in dfs(l, l+i-1):
                        for r_val in dfs(l+i+1, r) :
                            res.append(l_val + r_val)
                elif ch == '-':
                    for l_val in dfs(l, l+i-1):
                        for r_val in dfs(l+i+1, r) :
                            res.append(l_val - r_val)
                elif ch == '*':
                    for l_val in dfs(l, l+i-1):
                        for r_val in dfs(l+i+1, r) :
                            res.append(l_val * r_val)
            
            return res

        return dfs(0, n-1)

if __name__ == '__main__':
    sol = Solution()
    print(Solution().diffWaysToCompute("2-1-1"))