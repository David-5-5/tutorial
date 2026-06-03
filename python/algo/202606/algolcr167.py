# LCR series 同 3
class Solution:
    def dismantlingAction(self, arr: str) -> int:
        begin = 0
        maxSubLen = 0
        for i in range(len(arr)):
            index = arr[begin:i].find(arr[i])
            if index == -1:
                maxSubLen = max(maxSubLen, i-begin+1)
            else:
                begin = begin + index + 1    
        return maxSubLen