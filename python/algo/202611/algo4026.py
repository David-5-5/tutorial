class Solution:
    def maximumGap(self, skill: str, station: str) -> int:
        n, m = len(skill), len(station)
        if n == 1: return 0
        suf = [0] * n
        j = n-1
        for i in range(m-1, -1, -1):
            if station[i] == skill[j]:
                suf[j] = i
                j -= 1
                if j == 0: break
        j, ans = 0, 1
        for i in range(m):
            if station[i] == skill[j]:
                ans = max(ans, suf[j+1] - i)
                j += 1
                if j == n-1:break
        return ans


if __name__ == "__main__":
    print(Solution().maximumGap("aacbaaa", "aaacbabaac"))