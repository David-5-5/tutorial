from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        
        ans = []
        def dfs(l:int, r:int, par:str):
            if l + r == 2 * n:
                ans.append(par)
                return
            
            if l == r or l < n: dfs(l+1, r, par + "(")
            if l > r: dfs(l, r+1, par + ")")
        
        dfs(0, 0, "")
        return ans