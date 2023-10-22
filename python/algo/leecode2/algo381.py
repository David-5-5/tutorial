import random
class RandomizedCollection:

    def __init__(self):
        self.cache = []

    def insert(self, val: int) -> bool:
        if val in self.cache:
            self.cache.append(val)
            return False
        else:
            self.cache.append(val)
            return True


    def remove(self, val: int) -> bool:
        if val not in self.cache:
            return False
        
        inx = self.cache.index(val)
        self.cache[inx] = self.cache[len(self.cache)-1]
        del self.cache[len(self.cache)-1]
        return True


    def getRandom(self) -> int:
        return random.choice(self.cache)
