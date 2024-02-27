class Solution:
    def appealSum(self, s: str) -> int:
        # 求子数组不同元素数目的和
        # 设 f(l, r) 表示 nums[l..r] 中有几个不同元素
        # 维护 last[x] 表示元素 x 最近出现的下标是哪个（如果 x 是第一次出现，则 last[x] == -1），
        # 则有递推式:
        # f(l, r) = f(l, r - 1) + 1 // if l > last[nums[r]]
        # f(l, r) = f(l, r - 1) // if l <= last[nums[r]]
        # 也就是说，为了维护 f(l,r)我们需要一个支持区间加法的数据结构，用线段树即可实现。
        # ∑r=0~n-1 ∑l=0~r f(l,r)。
        # 如果只是求所有子数组不同元素数目之和，不需要知道 f(l,r)的具体数值。 
        # 设g(i)=∑l=0~i f(l,i) 那答案就是 ∑i=0~n−1 g(i), 同时
        # g(i) = g(i-1) + i - last[nums[i]]
        n = len(s)
        last = [-1] * 26
        ans, g = 0, 0
        for i in range(n):
            g += i - last[ord(s[i])-ord('a')]
            ans += g
            last[ord(s[i])-ord('a')] = i
        return ans

if __name__ == "__main__":
    sol = Solution()
    s = "abbca"
    print(sol.appealSum(s))