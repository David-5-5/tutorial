from functools import lru_cache
class Solution:
    def tallestBillboard(self, rods) -> int:
        '''
        官方题解，方法一动态规划
        '''
        @lru_cache(None)
        # 自行解答，多一维超时
        # def dp(i, s1, s2):
        #     if i == len(rods):
        #         return s2 if s1 == s2 else 0
        #     return max(dp(i + 1, s1, s2),
        #                dp(i + 1, s1 + rods[i], s2),
        #                dp(i + 1, s1, s2 + rods[i]))
        # return dp(0,0,0)
        def dp(i, s):
            if i == len(rods):
                return 0 if s == 0 else float('-inf') # s == 0 表示找到两组相等的钢管
            return max(dp(i + 1, s),
                       dp(i + 1, s - rods[i]), 
                       dp(i + 1, s + rods[i]) + rods[i]) # 优化，少一维
 
        return dp(0, 0)


    def tallestBillboard2(self, rods) -> int:
        '''
        官方题解，方法二暴力优化，折半法
        '''
        def combi(part):
            # part元素组合，特别巧妙
            # 每个元素由三种情况，X（集合1， a）， -X（集合2， b）， 不出现
            state = {(0,0)}
            for x in part:
                state |= {(a+x, b) for a, b in state} | \
                {(a, b+x) for a, b in state}
            
            delta = {}
            for a, b in state:
                delta[a-b] = max(a, delta.get(a-b, 0))
            return delta

        ans = 0
        left = combi(rods[0:len(rods)//2])
        right = combi(rods[len(rods)//2:])
        for d in left.keys():
            if -d in right.keys():
                ans = max(ans, left[d] + right[-d])
        return ans

    def tallestBillboard3(self, rods) -> int:
        # 将问题转化为求数组和为0时的组合, 对任何一个数，可以用三种方式对待它，乘以1，-1或0，目标是求和为0时的最大正数和
        # 例如，[1，2，3], 可以对1，2乘以1，3乘以-1，此时和为0， 最大正数和为1+2=3
        # 
        # 用字典来存储每一步的结果，键和值分别是(k:v) 总和以及正数和， 
        # 初始化时dp={0:0},表示和为0时的最大长度为0 那么最后只需要求dp[0]的最大值就ok
        # 遍历所有钢筋, 对每根钢筋都有三种处理方式：加，减，丢 （对应乘以1，-1或0）如：[1,2,3] 
        # 第一步: 用钢筋1，对初始的0，操作 如果加，那么总和是1，正数是1；如果减，总和是-1，正数0；
        #        如果丢，维持不变；更新dp={0:0, 1:1, -1:0}
        # 第二步: 用钢筋2，对第一步中dp的键0，1，-1的基础上分别进行“加，减，丢 ”的操作 在0:0基础上，
        #        如果加，也就是变为2：2；如果减，变为 -2：0； 如果丢，变成0：0 类似的，
        #        在1：1基础上，加减丢变为3：3，-1：1，1：1 类似的，在-1：0基础上，加减丢变为1：2，-3：0，-1：0
        #        每个键取较大值，用粗体标识了，然后更新dp={0:0, 1:2, 2:2, -1:1, 3:3, -2:0, -3:0} 总和为1时，
        #        相比第一步时的正数和为1，第二步时正数和变为了2，将dp[1]修改为更大的2 总和为-1时，相比第一步时的正数和为0，
        #        第二步时正数和变为了1，将dp[-1]修改为更大的1 最后返回dp[0]
        dp = {0: 0}
        for i in rods:
            for k, b in list(dp.items()):
                dp[k + i] = max(dp.get(k + i, 0), b + i)
                dp[k - i] = max(dp.get(k - i, 0), b)
        return dp[0]


if __name__ == "__main__":
    sol = Solution()
    # import random
    from datetime import datetime
    # nums = [random.randint(1, 200) for _ in range(32)]
    # begin = datetime.now()
    # print(f'The first result is {sol.tallestBillboard(nums)} and duration is {datetime.now()-begin}')
    # begin = datetime.now()
    # print(f'The second result is {sol.tallestBillboard2(nums)} and duration is {datetime.now()-begin}')
    begin = datetime.now()
    nums = [1,2,3]
    print(f'The third result is {sol.tallestBillboard3(nums)} and duration is {datetime.now()-begin}')
