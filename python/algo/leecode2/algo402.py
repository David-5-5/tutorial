class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        n = len(num)
        if k >= n : return "0"
        
        stack = []
        inx, left = 0, k
        while left and inx < n:
            while stack and stack[-1] > num[inx] and left:
                stack.pop(-1)
                left -= 1
            stack.append(num[inx])
            inx += 1
        ans = (''.join(stack)+num[inx:])[0:n-k].lstrip('0')
        return  "0" if ans == '' else ans

if __name__ == "__main__":
    sol = Solution()
    num, k = "1432219", 3
    print(sol.removeKdigits(num, k))