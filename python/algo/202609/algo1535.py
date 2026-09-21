from typing import List


class Solution:
    def getWinner(self, arr: List[int], k: int) -> int:
        cur, cnt, n = 0, 0, len(arr)
        
        for i in range(1, n):
            if arr[cur] > arr[i]:
                cnt += 1
            else:
                cur, cnt = i, 1
            if cnt == k: break
        
        return arr[cur]

