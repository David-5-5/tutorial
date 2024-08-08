from itertools import accumulate
from string import ascii_lowercase
from typing import List

c2i = {c : i for i, c in enumerate(ascii_lowercase)}

# 双周赛 85 自行解答 差分数组
class Solution:
    def shiftingLetters(self, s: str, shifts: List[List[int]]) -> str:
        diff = [0] * (len(s)+1)
        # diff = [0] * len(s)

        for b, e, d in shifts:
            diff[b] += d if d else -1
            diff[e+1] -= 1 if d else -1 # diff 长度加一，确保不越界
            # if e+1 < n: diff[e+1] -= 1 if d else -1
        
        # arr = list(accumulate(diff))
        # ans = [''] * len(s)
        # for i, c in enumerate(s):
        #     ans.append(chr((ord(c)-ord('a')+arr[i]+26)%26 + ord('a')))
        # return ''.join(ans)

        # return ''.join(chr((ord(c)-ord('a')+d+26)%26 + ord('a')) for c,d in zip(s, accumulate(diff)))
        return ''.join(ascii_lowercase[(c2i[c]+d)%26] for c,d in zip(s, accumulate(diff)))


if __name__ == '__main__':
    solution = Solution()
    s, shifts = "abc", [[0,1,0],[1,2,1],[0,2,1]]
    print(solution.shiftingLetters(s, shifts))

