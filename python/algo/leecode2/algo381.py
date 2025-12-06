from collections import defaultdict
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


# 2025.12.05 复习
# 数学算法 - 随机算法 - 6.1 随机数
class RandomizedCollection:

    def __init__(self):
        self.cache = []
        self.v2i = defaultdict(set)

    def insert(self, val: int) -> bool:
        ret = val not in self.v2i
        inx = len(self.cache)
        self.v2i[val].add(inx)
        self.cache.append(val)

        return ret


    def remove(self, val: int) -> bool:
        if val not in self.v2i:return False
        
        inx = self.v2i[val].pop()

        rep = self.cache[-1]
        self.cache.pop()
        if inx < len(self.cache) :
            self.cache[inx] = rep
            self.v2i[rep].remove(len(self.cache))
            self.v2i[rep].add(inx)

        if len(self.v2i[val]) == 0: del self.v2i[val]

        return True

    def getRandom(self) -> int:
        return random.choice(self.cache)

