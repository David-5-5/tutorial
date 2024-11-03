
class Solution:
    def isBalanced(self, num: str) -> bool:
        num1 = [int(i) for i in num]
        num2 = [0] + [int(i) for i in num]
        return sum(num1[::2]) == sum(num2[::2])
    
if __name__ == "__main__":
    sol = Solution()

    print(sol)