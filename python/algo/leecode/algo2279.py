# 周赛 294
class Solution:
    def maximumBags(self, capacity, rocks, additionalRocks: int) -> int:
        # 2022 11 851 ms
        if len(capacity) == 0:
            return 0
        
        n = len(capacity)
        attr = []
        fullCount = 0
        for i in range(n):
            if capacity[i] == rocks[i]:
                fullCount += 1
            else:
                attr.append(capacity[i] - rocks[i])
        
        attr.sort()
        additional = additionalRocks
        while len(attr) > 0 and attr[0] <= additional:
            fullCount += 1
            additional -= attr.pop(0)

        return fullCount
    
    def maximumBags2(self, capacity, rocks, additionalRocks: int) -> int:
        # 2024.9 重写 思路一致，贪心 + 排序 106 ms
        fullCount = 0
        to_fill  = sorted([x-y for x,y in zip(capacity, rocks)])

        for f in to_fill:
            if additionalRocks < f: break
            else:
                additionalRocks -= f
                fullCount += 1

        return fullCount
    
if __name__ == "__main__":
    sol = Solution()
    capacity, rocks, additionalRocks = [2,3,4,5], [1,2,4,4], 2
    print(sol.maximumBags(capacity, rocks, additionalRocks))