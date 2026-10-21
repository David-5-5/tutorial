from math import inf


class Solution:
    def minMoves(self, target: int, maxDoubles: int) -> int:
        
        def dfs(val: int, left:int) -> int:
            if val == 1: return 0
            if left == 0: return val - 1
            
            if val % 2: return 1 + dfs(val-1, left)
            else: return 1 + dfs(val//2, left-1)

        return dfs(target, maxDoubles)


if __name__ == "__main__":  
    print(Solution().minMoves(19, 2))