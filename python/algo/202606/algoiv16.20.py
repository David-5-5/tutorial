from typing import List


class Solution:
    def getValidT9Words(self, num: str, words: List[str]) -> List[str]:
        l2d = [2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9]
        ans = []
        for w in words:
            for i, ch in enumerate(w):
                d = l2d[ord(ch) - ord('a')]
                if ord(num[i])- ord('0') != d :
                    break
            else : ans.append(w)        
        return ans