from typing import List

# 周赛 344
class Solution:
    def colorTheArray(self, n: int, queries: List[List[int]]) -> List[int]:
        # 自行解答，模拟过程即可
        color = [0] * n
        cur = 0
        ans = []
        for i, c in queries:
            before = 0 # 更改前 i 相邻元素计数
            if i>0 and color[i]!=0 and color[i-1] == color[i]:before += 1
            if i+1<n and color[i]!=0 and color[i] == color[i+1]:before += 1

            color[i] = c
            after = 0 # 更改前 i 相邻元素计数
            if i>0 and color[i]!=0 and color[i-1] == color[i]:after += 1
            if i+1<n and color[i]!=0 and color[i] == color[i+1]:after += 1
            
            cur += after - before
        
            ans.append(cur)
        return ans

    
if __name__ == "__main__":
    sol = Solution()
    n, queries = 4, [[0,2],[1,2],[3,1],[1,1],[2,1]]
    print(sol.colorTheArray(n, queries))