from itertools import permutations

# 周赛 356
class Solution:
    def minimumString(self, a: str, b: str, c: str) -> str:
        # 参考视频题解
        def merge(s: str, t: str) -> str:
            if s in t: return t
            if t in s: return s

            for i in range(min(len(s), len(t)), 0,-1):
                if s[-i:] == t[:i]: # 从大到小判断重合
                    return s + t[i:] 
            return s + t # 完全不重合
        
        ans = ""
        for a, b, c in permutations((a, b, c)):
            s = merge(merge(a, b), c)
            if ans == "" or len(ans) > len(s) or len(ans) == len(s) and ans > s:
                ans = s
        return ans


if __name__ == "__main__":
    sol = Solution()
    a, b, c = "abc", "bca", "aaa"
    print(sol.minimumString(a, b, c))