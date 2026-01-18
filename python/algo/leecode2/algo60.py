from typing import List
from math import factorial
class Solution:
    def getPermutation(self, n: int, k: int) -> str:

        def permutation(ds:List[int], k):
            if k == 1: return ''.join([str(i) for i in ds])
            if k == factorial(len(ds)) : return ''.join([str(i) for i in ds[::-1]])

            m, rem = k // factorial(len(ds)-1), k % factorial(len(ds)-1)
            if rem == 0:
                head = str(ds.pop(m-1))
                return head + ''.join([str(i) for i in ds[::-1]])
            head = ds.pop(m)
            return str(head) + permutation(ds, rem)

        digits = [i for i in range(1, n+1)]
        return permutation(digits, k)
    
    def getPermutation2(self, n: int, k: int) -> str:
        # 优化实现，去除冗余判断
        def permutation(ds:List[int], k):
            if k == 0: return ''.join([str(i) for i in ds])
            if k == factorial(len(ds))-1: return ''.join([str(i) for i in ds[::-1]])

            m, rem = divmod(k, factorial(len(ds)-1))
            head = ds.pop(m)
            return str(head) + permutation(ds, rem)

        digits = [i for i in range(1, n+1)]
        return permutation(digits, k-1)
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.getPermutation(3, 2))