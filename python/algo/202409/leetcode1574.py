from typing import List

# 同 双周赛120   2972
class Solution:
    def findLengthOfShortestSubarray(self, arr: List[int]) -> int:
        n = len(arr)
        i, j = 0, n-1

        # 后缀非递减
        while j > 0 and arr[j-1] <= arr[j]:
            j -= 1
        res = j
        if j == 0: return 0 # 整个队列非递减

        # 前缀非递减
        while i+1 < n and arr[i] <= arr[i+1]:
            i += 1

        # 保留前缀或后缀最小删除长度
        res = min(res, n - i - 1)

        j = n-1
        while i >= 0:
            # 删除中间的队列的长度
            while arr[i] <= arr[j] and (j==n-1 or arr[j]<=arr[j+1]): 
                j -= 1
            res = min(res, j - i) # 当前
            i -= 1
        return res


if __name__ == "__main__":
    sol = Solution()
    arr = [1,2,3,10,4,2,3,5]
    arr = [6,3,10,11,15,20,13,3,18,12]
    print(sol.findLengthOfShortestSubarray(arr))
