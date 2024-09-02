from typing import Counter, List

# 周赛 309
class Solution:
    def longestNiceSubarray(self, nums: List[int]) -> int:
        # 自行解答 执行时间 4119 ms
        cnt = Counter()
        l = -1
        def contain(s:set) -> bool:
            for v in s:
                if cnt[v] == 1: return True
            return False
        ans = 0
        for r, v in enumerate(nums):
            cur = set()
            for i in range(32):
                if v >> i & 1:
                    cur.add(i)
            while contain(cur):
                l += 1
                for i in range(32):
                    if nums[l] >> i & 1:
                        cnt[i] -= 1
            for c in cur: cnt[c] += 1
            ans = max(ans, r-l)
        return ans

    def longestNiceSubarray2(self, nums: List[int]) -> int:
        # 自行解答，使用 +, -, | 运算代替集合运算
        # 优化后执行时间 108 ms
        l = -1
        sum = ans = 0
        for r, v in enumerate(nums):
            while sum | v != sum + v:
                l += 1
                sum -= nums[l]
            sum += v
            if ans < r-l: ans = r-l
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1,3,8,48,10]
    nums = [135745088,609245787,16,2048,2097152]
    print(sol.longestNiceSubarray(nums))
    print(sol.longestNiceSubarray2(nums))