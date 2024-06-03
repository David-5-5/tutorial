from typing import List
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        # refer to python/dsaa/backtracing.py
        # 使用回溯子集型回溯的模板一
        m = n * 2
        path = [''] * m # [], 使用append/pop 操作

        ans = []
        def dfs(i, open):
            if i == m:
                ans.append(''.join(path))
                return
            
            # 不选: 选close parenthesis
            if  i-open < open:
                path[i] = ')'
                dfs(i+1, open)
            
            # 选 open parenthesis
            if open < n:
                path[i] = '('
                dfs(i+1, open+1)
            
            # 由于 path初始化为固定长度数组，且返回定长的path，因此不需要回溯操作
        dfs(0, 0)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.generateParenthesis(3))