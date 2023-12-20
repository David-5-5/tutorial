from typing import List
import math
class Solution:
    def getNandResult(self, k: int, arr: List[int], operations: List[List[int]]) -> int:
        '''拆位计算, 按位采用线段树进行按位的计算, 这样左值为0或1, 
        dp包含两个数据, 分别表明与非门的左值为0, 1, 这样便于区段的合并, 并代替结合律
        '''
        n= len(arr)
        
        # 按位与非操作的 0 NAND 0, 1都为 1, 1 NAND 0, 1 分别为 1, 0
        # 因此按位:
        # dp[x][0] 表示左值为0, 穿过当前区段的结果, k位都是1 
        # dp[x][1] 表示左值为1, 穿过当前区段的结果, 相当于和当前值按位异或
        dp = [[0]*2 for _ in range((2 ** (math.ceil(math.log(n, 2))+1) - 1))]
        
        
        def set(inx: int, val:int):
            dp[inx][1] = dp[inx][0] ^ val

        def pushup(p: int):
            l, r = p*2+1, p*2+2
            for i in range(k):
                # '>>i & 1' 将第i位右移到最后一位, 并消除掉除最后一位的 1
                # 完成操作后'1 << i', 再左移到i位, 并按位或, 合并位操作结果
                dp[p][0] |= dp[r][dp[l][0]>>i & 1] >> i & 1 << i
                dp[p][1] |= dp[r][dp[l][1]>>i & 1] >> i & 1 << i


        def build(l: int, r: int, p: int):
            '''Build the segment tree
            l, current left inx of segment, start with 0
            r, current right inx of segment, start with 0
            p, the inx of tree(dp), 0 is root
            '''
            dp[p][0] = 1 << k -1
            if l == r:
                set(p, arr[l])
                return
            
            mid = (l + r) // 2
            build(l, mid, p*2+1)
            build(mid+1, r, p*2+2)
            pushup(p)

        def update(l: int, r: int, p: int, inx:int, val:int):
            if l == r:
                set(p, val)
            mid = (l + r) // 2
            if mid >= inx:
                update(l, mid, p*2+1, inx, val)
            else:
                update(mid+1,r,p*2+2, inx, val)
            pushup(p)

        build(0, n-1, 0)
        
        ans = 0
        for op in operations:
            if op[0] == 0:
                update(0, n-1, 0, op[1], op[2])
                continue
            
            for i in range(k):
                x, y = op[1], op[2] >> i & i
                res = dp[0][y] >> i & i
                if y != res and not (x == 1 or dp[res] >> i & i == res):
                    res = y ^ x%2

                ans ^= res << i
                
        return ans        
        

if __name__ == "__main__":
    sol = Solution()
    k, arr, operations = 3, [1,2], [[1,2,3],[0,0,3],[1,2,2]]
    print(sol.getNandResult(k, arr, operations))