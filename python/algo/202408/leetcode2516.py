#  周赛 325 双指针，前后缀满足条件的最小值
#  首先取出满足条件的后缀，再枚举前缀，不断减少后缀，找出满足条件的最小值
class Solution:
    def takeCharacters(self, s: str, k: int) -> int:
        n = j = len(s)
        c = {'a':0, 'b':0, 'c':0}
        while c['a'] < k or c['b'] < k or c['c'] < k:
            if j == 0:return -1
            j -= 1
            c[s[j]] += 1
        
        ans = n - j

        for i in range(n):
            c[s[i]] += 1
            while j < n and c[s[j]] > k:
                c[s[j]] -= 1
                j += 1
            ans = min(ans, i + n - j + 1)
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.takeCharacters("aabaaaacaabc", 2))
    

        
