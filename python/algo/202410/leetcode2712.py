# 周赛 347
class Solution:
    def minimumCost(self, s: str) -> int:
        # 自行解答
        sl, n = list(s), len(s)
        ans = 0
        for i in range(n-1):
            if s[i]!=s[i+1]:
                ans += min(i+1,n-i-1)
        return ans
    
if __name__ == "__main__":
    sol = Solution()            
    s = "010101"
    print(sol.minimumCost(s))