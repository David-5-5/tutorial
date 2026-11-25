class Solution:
    def numOfBurgers(self, tomatoSlices: int, cheeseSlices: int) -> list[int]:
        if cheeseSlices == 0: 
            if tomatoSlices == 0: return [0, 0]
            else: return []
        ratio = tomatoSlices / cheeseSlices
        if ratio < 2 or ratio > 4 or tomatoSlices % 2: return []

        jumbo = (tomatoSlices -  2 * cheeseSlices) // 2
        return [jumbo, cheeseSlices - jumbo]