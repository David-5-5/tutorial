from math import comb

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def numOfWays(self, nums) -> int:
        return  (self.numOfWaysIt(nums) -1)  % (10 ** 9 + 7)
    
    def numOfWaysIt(self, nums) -> int:
        n = len(nums)
        if n < 3 : return 1
        
        less = []
        great = []
        for i in range(1, n):
            if nums[i] < nums[0]:
                less.append(nums[i])
            else:
                great.append(nums[i])
        return self.Combinatorial(n-1, len(less)) * self.numOfWaysIt(less) * self.numOfWaysIt(great) 

    def Combinatorial(self,n,i) :
        #n>=i
        Min=min(i,n-i)
        result:int=1
        for j in range(0,Min):
            #由于浮点数精度问题不能用//
            result = result * (n-j) // (j + 1)
        return  int(result)

    def numOfWays2(self, nums) -> int:
        # 2025.10.6 复习
        def dfs(nums) -> int:
            n = len(nums)
            if n < 3 : return 1
            
            less = []
            great = []
            for i in range(1, n):
                if nums[i] < nums[0]:
                    less.append(nums[i])
                else:
                    great.append(nums[i])
            return comb(n-1, len(less)) * dfs(less) * dfs(great) 

        return  (dfs(nums) -1)  % (10 ** 9 + 7)
    
if __name__ == '__main__':
    sol = Solution()
    nums = [3,4,5,1,2]
    print(sol.numOfWays(nums))
