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

if __name__ == '__main__':
    sol = Solution()
    # nums = [2,1,3]
    # nums = [3,4,5,1,2]
    # nums = [1,2,3]
    # nums = [3,1,2,5,4,6]
    # nums = [9,4,2,1,3,6,5,7,8,14,11,10,12,13,16,15,17,18]
    # nums = [10,23,12,18,4,29,2,8,41,31,25,21,14,35,26,5,19,43,22,37,9,20,44,28,1,39,30,38,36,6,13,16,27,17,34,7,15,3,11,24,42,33,40,32]
    nums = [74,24,70,11,6,4,59,9,36,82,80,30,46,31,22,34,8,69,32,57,18,21,37,83,55,38,41,72,48,65,27,60,73,58,68,50,16,77,75,20,81,3,61,13,10,29,62,49,12,66,39,45,28,40,42,52,78,56,44,17,14,67,35,26,19,5,63,51,43,23,79,2,54,47,76,53,7,25,64,33,1,15,71]
    print(sol.numOfWays(nums))
    print(sol.Combinatorial(17,8))
