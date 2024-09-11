from bisect import bisect_left
from collections import defaultdict
from typing import List

# 周赛 303
class FoodRatings:

    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):
        self.fh = defaultdict(int)
        self.ch = defaultdict(list)
        for f, c, r in zip(foods,cuisines, ratings):
            self.fh[f] = (r, c)
            inx = bisect_left(self.ch[c], (-r, f))
            self.ch[c].insert(inx, (-r, f))

    def changeRating(self, food: str, newRating: int) -> None:
        old, c = self.fh[food]
        self.fh[food] = (newRating, c)
        inx = bisect_left(self.ch[c], (-old, food))
        self.ch[c].pop(inx)
        inx = bisect_left(self.ch[c], (-newRating, food))
        self.ch[c].insert(inx, (-newRating, food))

    def highestRated(self, cuisine: str) -> str:
        return self.ch[cuisine][0][1]


# Your FoodRatings object will be instantiated and called as such:
# obj = FoodRatings(foods, cuisines, ratings)
# obj.changeRating(food,newRating)
# param_2 = obj.highestRated(cuisine)