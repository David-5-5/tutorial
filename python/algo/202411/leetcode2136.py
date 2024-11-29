from typing import List

# 贪心专题 交换论证法
class Solution:
    def earliestFullBloom(self, plantTime: List[int], growTime: List[int]) -> int:
        # 自行解答，看上去很复杂，其实很简单
        ans = begin = 0
        # 按 growTime 时间 倒序排序
        for p, g in sorted(zip(plantTime, growTime), key=lambda p:-p[1]):
            begin += p
            ans = max(ans, begin + g)
        return ans

if __name__ == "__main__":
    sol = Solution()
    plantTime, growTime = [1,4,3], [2,3,1]
    print(sol.earliestFullBloom(plantTime, growTime))