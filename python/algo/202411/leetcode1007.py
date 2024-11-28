from math import inf
from typing import List

# 贪心专题 先枚举，再贪心
class Solution:
    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        # 自行解答，第一个元素分别和后面元素比较，四种情况：
        # top[0] 在 top          和后续的tops, bottoms比较需要旋转次数
        #        旋转到bottom(+1) 和后续的tops, bottoms比较需要旋转次数
        # botton[0] 在 bottom    和后续的tops, bottoms比较需要旋转次数
        #        旋转到 top(+1)   和后续的tops, bottoms比较需要旋转次数
        # 比较罗嗦
        ans = inf
        
        res, fst = 0, tops[0]
        for t, b in zip(tops[1:], bottoms[1:]):
            if fst == t:
                continue
            elif fst == b: res += 1
            else:
                res = -1
                break
        if res != -1: ans = min(ans, res)
        
        res, fst= 1, tops[0]
        for t, b in zip(tops[1:], bottoms[1:]):
            if fst == b:
                continue
            elif fst == t: res += 1
            else:
                res = -1
                break
        if res != -1: ans = min(ans, res)

        res, fst = 0, bottoms[0]
        for t, b in zip(tops[1:], bottoms[1:]):
            if fst == b: 
                double += 1
                continue
            elif fst == t: res += 1
            else:
                res = -1
                break
        if res != -1: ans = min(ans, res)
        
        res, fst = 1, bottoms[0]
        for t, b in zip(tops[1:], bottoms[1:]):
            if fst == t: 
                continue
            elif fst == b: res += 1
            else:
                res = -1
                break
        if res != -1: ans = min(ans, res)
        return -1 if ans == inf else ans

    def minDominoRotations2(self, tops: List[int], bottoms: List[int]) -> int:
        # 基于上述方法优化, 抽象出公共方法
        def check(fst:int, one: List[int], other:List[int]):
            res = 0
            for t, b in zip(one, other):
                if fst == t:
                    continue
                elif fst == b: res += 1
                else:
                    return inf
            return res
        
        ans = inf
        ans = min(ans, check(tops[0], tops[1:], bottoms[1:]))
        ans = min(ans, check(tops[0], bottoms[1:], tops[1:])+1)
        ans = min(ans, check(bottoms[0], tops[1:], bottoms[1:])+1)
        ans = min(ans, check(bottoms[0], bottoms[1:], tops[1:]))
        
        return -1 if ans == inf else ans
    
if __name__ == "__main__":
    sol = Solution()
    tops, bottoms =[2,1,1,3,2,1,2,2,1], [3,2,3,1,3,2,3,3,2]
    print(sol.minDominoRotations(tops, bottoms))
    print(sol.minDominoRotations2(tops, bottoms))