class Solution:
    def uniqueLetterString(self, s: str) -> int:
        # 参考 [2262], 递推式变更为：
        # f(l, r) = f(l, r - 1) + 1 // if l > last[nums[r]], 需增加的数量为 i - last[nums[r]]
        # f(l, r) = f(l, r - 1) - 1 // if stl[nums[r]] < l <= last[nums[r]], 需减去的数量为last[nums[r]] - stl[nums[r]]
        # f(l, r) = f(l, r - 1)     // if l <= stl[nums[r]]
        # last, stl 初始化为 -1
        last = [-1] * 26
        # The second-to-last
        stl = [-1] * 26
        ans, g = 0, 0
        for i, ch in enumerate(s):
            chord = ord(ch)-ord('A')
            g += i - 2 * last[chord] + stl[chord]
            ans += g
            stl[chord] = last[chord]
            last[chord] = i
        return ans

if __name__ == "__main__":
    sol = Solution()
    s = "AAA"
    print(sol.uniqueLetterString(s))