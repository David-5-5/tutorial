class Solution:
    def filter(self, nums:list):
        result = filter(lambda x: x>2, nums)
        nums = list(result)
        nums.sort()
        print(len(nums))

if __name__ == '__main__':
    sol = Solution()
    from datetime import datetime
    import random
    begin = datetime.now()
    nums = [random.randint(-10000, 10000) for _ in  range(19999999)] 
    print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    sol.filter(nums)
    print((datetime.now()- begin).total_seconds())
