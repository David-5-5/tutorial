from typing import Counter, List

# 周赛 368
class Solution:
    def minGroupsForValidAssignment(self, balls: List[int]) -> int:
        # 参考题解
        cnt = Counter(balls)

        min_k = min(cnt.values())
        # 时间复杂度 O(min_k * len(cnt)) = O(n)
        # 另 x = min_k, x + (x+1) + ... + (x+m-1) = (2x+m-1)*m = n
        # 因此 二重循环次数 x * m <= (2x + m -1) * m = n
        for k in range(min_k, 0, -1):
            ans = 0
            for c in cnt.values():
                # q, r =  c // k, c % k
                q, r = divmod(c, k)
                if q < r:
                    ans = 0
                    break
                else:
                    # ans = ceil(c / k + 1)
                    ans += (c + k) // (k + 1)
            if ans: return ans
    

if __name__ == "__main__":
    sol = Solution()
    balls = [10,10,10,3,1,1]
    print(sol.minGroupsForValidAssignment(balls))