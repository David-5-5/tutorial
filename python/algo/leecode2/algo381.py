from sortedcontainers import SortedDict
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
        if val in self.cache:
            self.cache.remove(val)
            return True
        else:
            return False


    def getRandom(self) -> int:
        return random.choice(self.cache)
