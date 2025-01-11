# 周赛 332, 前后缀分解
class Solution:
    def minimumScore(self, s: str, t: str) -> int:
        n , m = len(s), len(t)
        # suf[i] 表示匹配了从 i 开始匹配了 t[suf[i]:] 的字符 
        # 若 suf[i] = m, 匹配 t 中 0 个字符
        # 若 suf[i] = 0, 匹配 t 中 所有字符
        
        # 前后缀 字符串匹配 模板
        # 模板 开始 后缀匹配
        suf = [m] * (n + 1)
        j = m
        for i in range(n-1, -1, -1):
            if j and s[i] == t[j-1]:
                j -= 1
            suf[i] = j

        
        ans = suf[0]
        j = 0
        for i in range(n):
            if s[i] == t[j]:
                # 前缀匹配
                j += 1
                # 以上是模板
                if suf[i] >= j:
                    ans = min(ans, suf[i+1] - j)
            if j == m: break
        return ans

if __name__ == "__main__":
    
    solution = Solution()
    s, t = "abacaba", "bzaa"
    print(solution.minimumScore(s, t))