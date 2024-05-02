from typing import List
from collections import defaultdict
class Solution:
    def stoneGameIX(self, stones: List[int]) -> bool:
        n = len(stones)
        
        # 本题仅关注数模3的余数，以及对应余数0，1，2的数量，用字典存储
        # 分析，当不存在整数3的数时，下列余数序列不被3整除
        # 1，1，2，1，2，1，2，1，2，...
        # 2，2，1，2，1，2，1，2，1, ...
        # 都是不被3整除的序列，存在规律，当序列数量为
        #   a)  偶数时，先手的数是后手比后手数量多2
        #   b)  奇数时，先手的数是后手比后手数量多1
        # 判断规Alice先手，先取取数量少的余数，导致序列被3整除，同时由于存在整数3的数量
        # 1，当整数3的数量mod == 1，由于Alice起始不能取整数3的数，因此判断仅存在一个整除3的数，由Bob取得
        #    此时整除3余1及2的数的数量相差大于2，Alice必胜
        # 2，当整数3的数量mod == 0，整数3的数，双方各取一个，可以等价于不存在整数3的数，
        #    余数1，2的数量之和大于2，Alice必胜
        # 例外，当仅有余1或余2的数时，Bob必胜

        dict3 = defaultdict(lambda: 0)
        for i in range(n):
            dict3[stones[i]%3] += 1
        if dict3[0]%2 == 0 and dict3[1] == 0 or dict3[2] == 0:
            return False
        elif dict3[0]%2 == 0 and dict3[1]==1 and dict3[2]==1:
            return True
        elif dict3[0]%2 == 0 and dict3[1] + dict3[2] > 2:
            return True
        elif dict3[0]%2 == 1 and  abs(dict3[1]-dict3[2]) >2:
            return True
        
        return False

if __name__ == "__main__":
    sol = Solution()
    stones = [[3,9,1,1,1,7,9]]    
    print(sol.stoneGameIX(stones))