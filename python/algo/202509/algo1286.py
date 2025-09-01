from itertools import combinations

# 回溯 - 4.4 组合型回溯
class CombinationIterator:

    def __init__(self, characters: str, combinationLength: int):
        self.characters = characters
        self.combs = list(combinations(range(len(characters)), combinationLength))
        self.cur = 0
    
    def next(self) -> str:
        ret = ""
        for i in self.combs[self.cur]:
            ret += self.characters[i]
        self.cur += 1
        return ret

    def hasNext(self) -> bool:
        return self.cur < len(self.combs)
