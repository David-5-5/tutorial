from typing import List
class Solution:
    def getNandResult(self, k: int, arr: List[int], operations: List[List[int]]) -> int:
        n, m = len(arr), len(operations)


    def nand(self, k: int, op1: int, op2: int):
        return 2 ** k - 1 - (op1 & op2)

    def nand2(self, k: int, op1: int, op2: int):
        return (2 ** k - 1 - op1) & (2 ** k - 1 - op2)

if __name__ == "__main__":
    sol = Solution()

    y = 3
    x = [2, 1, 3]
    for i in range(len(x)):
        y = sol.nand(3, y, x[i % len(x)])
    print(y)
