from typing import List


class Solution:
    def shiftDistance(self, s: str, t: str, nextCost: List[int], previousCost: List[int]) -> int:
        next = [[0]*26 for _ in range(26)]
        prev = [[0]*26 for _ in range(26)]

        for i in range(26):
            for j in range(1, 26):
                i_n = (i + j) % 26
                i_n_p = (i_n - 1) % 26
                next[i][i_n] = next[i][i_n_p] + nextCost[i_n_p]
        
        for i in range(26):
            for j in range(1, 26):
                i_n = (i-j) % 26
                i_n_p = (i_n + 1) % 26
                prev[i][i_n] = prev[i][i_n_p] + previousCost[i_n_p]

        ans = 0
        for src, tar in zip(s, t):
            ans += min(next[ord(src)-ord('a')][ord(tar)-ord('a')], prev[ord(src)-ord('a')][ord(tar)-ord('a')])
        return ans

if __name__ == "__main__":
    sol = Solution()
    s, t, nextCost, previousCost = "ccdbbcaadb", "aadbbdaaac" , [6,6,9,8,2,4,10,10,6,4,9,5,5,5,2,7,9,7,4,1,4,10,1,5,2,4], [0,4,5,6,7,10,5,5,8,1,1,10,7,8,10,8,7,2,3,3,6,3,0,6,4,0]
    print(sol.shiftDistance(s, t, nextCost, previousCost))
