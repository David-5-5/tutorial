from typing import List

# 贪心专题
class Solution:
    def maximumEvenSplit(self, finalSum: int) -> List[int]:
        if finalSum % 2 : return []
        ans, begin =[], 2
        while begin * 2 < finalSum:
            ans.append(begin)
            finalSum -= begin
            begin += 2

        ans.append(finalSum)
        return ans
        
