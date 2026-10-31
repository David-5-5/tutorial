class Solution:
    def matchPlayersAndTrainers(self, players: list[int], trainers: list[int]) -> int:
        players.sort()
        trainers.sort()
        i, j, m, n = 0, 0, len(players), len(trainers)
        while i < m and j < n:
            if players[i] <= trainers[j]:
                i += 1
            j += 1
        return i