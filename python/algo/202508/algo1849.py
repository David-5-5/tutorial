#  回溯 - 4.3 划分型回溯
class Solution:
    def splitString(self, s: str) -> bool:
        n = len(s)
        
        def dfs(i: int, prev: int) -> bool:
            if i == n:
                return prev != int(s)
            
            for j in range(i + 1, n + 1):
                cur_str = s[i:j]
                cur = int(cur_str)
                
                if prev == -1 or cur + 1 == prev:
                    if dfs(j, cur):
                        return True
            
            return False
        
        return dfs(0, -1)