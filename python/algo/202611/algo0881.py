class Solution:
    def numRescueBoats(self, people: list[int], limit: int) -> int:
        n = len(people)
        people.sort()
        i, j, ans = 0, n - 1, 0
        while i <= j:
            if i == j or people[i] + people[j] <= limit:
                ans += 1
                i += 1
                j -= 1
            else:
                ans += 1
                j -= 1
        return ans