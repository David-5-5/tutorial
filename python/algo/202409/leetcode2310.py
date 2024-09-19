# 周赛 298
class Solution:
    def minimumNumbers(self, num: int, k: int) -> int:
        if num == 0: return 0
        # 求最小值，最多为 10
        for i in range(1, 11):
            if num < i * k :break
            if (num - i * k) % 10 == 0:
                return i

        return -1


if __name__ == "__main__":
    sol = Solution()
    print(sol.minimumNumbers(58, 9))
