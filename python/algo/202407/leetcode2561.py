from typing import Counter, List

# 周赛 331
class Solution:
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        # 参考题解
        cnt = Counter()
        min_k = min(min(basket1),min(basket2))

        for x, y in zip(basket1, basket2):
            cnt[x] += 1
            cnt[y] -= 1
        
        pos = [] # basket1 多出的部分，需要转移到 basket2
        neg = [] # basket2 多出的部分， 需要转移到 basket1

        for k, c in cnt.items():
            if c % 2 : return -1 # 奇数，不能分配平均分配
            if c > 0:
                pos.extend([k] * (c // 2))
            elif c < 0:
                neg.extend([k] * (-c // 2))
        pos.sort()             # 从小到大排序    
        neg.sort(reverse=True) # 从大到小排序，最小化交换代价

        ans = 0
        for k1, k2 in zip(pos,neg):
            # 关键点，有两种交换方式: 2024.11.27
            # 1, k1,k2 进行一次交换，成本 min(k1,k2)
            # 2, k1,k2 与 min_k 元素进行两次交换，成本为 2 * min_k
            # 最后取两者的最小值
            ans += min(min(k1,k2), 2 * min_k)

        return ans


if __name__ == "__main__":
    sol = Solution()
    basket1, basket2 = [2,3,4,1], [3,2,5,1]
    basket1, basket2 = [4,2,2,2], [1,4,1,2]
    print(sol.minCost(basket1, basket2))