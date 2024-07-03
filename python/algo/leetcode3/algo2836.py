from typing import List

class Solution:
    def getMaxFunctionValue(self, receiver: List[int], k: int) -> int:
        n = len(receiver)

        lg = k.bit_length()
        pa = [ [(p,p)] + [None] * (lg-1) for p in receiver]

        for e in range(1, lg):
            for i in range(n):
                p, s = pa[i][e-1]
                pp, ss = pa[p][e-1]
                pa[i][e] = (pp, s + ss)
        
        ans = 0
        for i in range(n):
            x = sum = i
            for j in range(lg):
                if k >> j & 1:
                    x, s = pa[x][j]
                    sum += s
            ans = max(ans, sum)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    receiver = [2,0,1]
    k = 4
    print(sol.getMaxFunctionValue(receiver, k))