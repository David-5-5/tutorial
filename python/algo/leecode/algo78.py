class Solution:
    def subsets(self, nums):
        # 初始化的子集合，默认为包含一个元素的空集合
        result = [[]]
        for digit in nums:
            ext = []
            for sub in result:
                '''
                对每一个nums的中每一数字, 结合当前的集合列表，对每个集合：
                1, Add current digit of nums
                2, Don't add current digit of nums, 
                Each time, the count of result will double
                '''
                newsub = sub.copy()
                newsub.append(digit)
                ext.append(newsub)
            result.extend(ext)
        return result

    def subsets2(self, nums):
        # 初始化的子集合，默认为包含一个元素的空集合
        result = [[]]
        for digit in nums:
            result.extend([subset.append(digit) for subset in result])
        return result



if __name__ == "__main__":
    sol = Solution()
    nums = [1,2,3]
    print(sol.subsets(nums))
    print(sol.subsets2(nums))
