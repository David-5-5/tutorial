class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        begin = 0
        maxSubLen = 0
        for i in range(len(s)):
            index = s[begin:i].find(s[i])
            if index == -1:
                maxSubLen = max(maxSubLen, i-begin+1)
            else:
                begin = begin + index + 1    
        return maxSubLen

if __name__ == "__main__":
    sol = Solution()
    print(sol.lengthOfLongestSubstring("bbtablud"))
