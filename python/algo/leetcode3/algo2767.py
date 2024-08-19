from math import inf

# 双周赛 108

matches = [bin(5**i)[2:] for i in range(7)]
class Solution:
    def minimumBeautifulSubstrings(self, s: str) -> int:
        

        n = len(s)
        # dfs[i] 表示 s[i:] 最少分割子串
        def dfs(i):
            if i == n:
                return 0
            if s[i] == '0':
                 # 不合法情况，求最小值时，返回 inf， 求最大值时，返回 -inf
                return inf
            ans = inf
            for j in range(i, n):
                # 枚举子串并检查子串是否合法
                if s[i:j+1] not in matches:
                    continue
                # 递归计算子串数量
                ans = min(ans, 1 + dfs(j+1))
            return ans
        res =  dfs(0)
        return -1 if res == inf else res

    def minimumBeautifulSubstrings2(self, s: str) -> int:
    
        n = len(s)
        # dfs[i] 表示 s[i:] 最少分割子串
        # 题目的长度太小，用cache反而更慢
        def dfs(i):
            if i == n:
                return 0
            if s[i] == '0':
                 # 不合法情况，求最小值时，返回 inf， 求最大值时，返回 -inf
                return inf
            ans = inf
            # 减少循环范围，提高效率
            for t in matches:
                if i + len(t) > n:
                    break
                # 递归计算子串数量
                if s[i:i+len(t)] == t:
                    ans = min(ans, 1 + dfs(i+len(t)))
            return ans
        res =  dfs(0)
        return -1 if res == inf else res
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.minimumBeautifulSubstrings("1011"))
    print(sol.minimumBeautifulSubstrings2("1011"))