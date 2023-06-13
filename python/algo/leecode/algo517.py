class Solution:
    def findMinMoves(self, machines) -> int:
        tot = sum(machines)
        n = len(machines)
        if tot % n :
            return -1
        tot = sum(machines)
        n = len(machines)
        avg = tot // n
        ans, s = 0, 0

        for num in machines:
            num -= avg
            s += num
            ans = max(ans, abs(s), num)
        return ans

