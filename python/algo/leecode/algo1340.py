class Solution:
    def maxJumps(self, arr, d: int) -> int:
        n = len(arr)
        dp = [0 for _ in range(n)]

        def dfs(inx: int):
            if dp[inx] != 0: return dp[inx]
            
            l = []
            r = []
            for i in range(1, d+1):
                if inx - i >=0 and arr[inx-i] < arr[inx]:
                    l.append(inx - i)
                else:
                    break;

            for i in range(1, d+1):
                if inx + i < n and arr[inx + i] < arr[inx]:
                    r.append(inx + i)
                else:
                    break;
            
            dp[inx] = 1
            if not l and not r:
                return dp[inx]
            
            l.extend(r)
            while l:
                dp[inx] = max(dp[inx], dfs(l.pop(-1))+1)
            
            return dp[inx]

        for i in range(n):
            dfs(i)
        
        return max(dp)
        

if __name__ == "__main__":
    sol = Solution()
    arr, d = [6,4,14,6,8,13,9,7,10,6,12], 2
    # arr, d = [3,3,3,3,3], 3
    # arr, d = [7,6,5,4,3,2,1], 1
    print(sol.maxJumps(arr, d))
    

