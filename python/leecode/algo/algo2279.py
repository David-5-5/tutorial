class Solution:
    def maximumBags(self, capacity, rocks, additionalRocks: int) -> int:
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

if __name__ == "__main__":
    sol = Solution()
    capacity, rocks, additionalRocks = [2,3,4,5], [1,2,4,4], 2
    print(sol.maximumBags(capacity, rocks, additionalRocks))