class Solution:
    def filterRestaurants(self, restaurants: list[list[int]], veganFriendly: int, maxPrice: int, maxDistance: int) -> list[int]:
        return [id for id, _ in sorted([[id, r] for id, r, v, p, d in restaurants if v>=veganFriendly and p <=maxPrice and d <=maxDistance ] , key=lambda row:(-row[1], -row[0]))] 

    def filterRestaurants2(self, restaurants: list[list[int]], veganFriendly: int, maxPrice: int, maxDistance: int) -> list[int]:
        restaurants.sort(key=lambda r: (-r[1], -r[0]))
        return [id for id, r, v, p, d in restaurants if v>=veganFriendly and p <=maxPrice and d <=maxDistance]    