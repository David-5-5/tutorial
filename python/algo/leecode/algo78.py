class Solution:
    def subsets(self, nums):
        result = [[]]
        for digit in nums:
            ext = []
            for sub in result:
                newsub = sub.copy()
                newsub.append(digit)
                ext.append(newsub)
            result.extend(ext)
        return result

if __name__ == "__main__":
    sol = Solution()
    nums = [1,2,3]
    print(sol.subsets(nums))
