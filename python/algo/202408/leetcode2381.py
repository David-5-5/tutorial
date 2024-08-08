from itertools import accumulate
from typing import List

# 双周赛 85 自行解答 差分数组
class Solution:
    def shiftingLetters(self, s: str, shifts: List[List[int]]) -> str:
        diff = [0] * len(s)

        for b, e, d in shifts:
            diff[b] += d if d else -1
            if e+1 < len(s): diff[e+1] -= 1 if d else -1
        
        arr = list(accumulate(diff))

        ans = [''] * len(s)
        for i, c in enumerate(s):
            ans.append(chr((ord(c)-ord('a')+arr[i]+26)%26 + ord('a')))

        return ''.join(ans)

if __name__ == '__main__':
    solution = Solution()
    s, shifts = "abc", [[0,1,0],[1,2,1],[0,2,1]]
    print(solution.shiftingLetters(s, shifts))

