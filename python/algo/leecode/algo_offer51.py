class Solution:
    # 题目变更为 LCR 170 
    total = 0
    def reversePairs(self, nums) -> int:
        if len(nums) < 2:return 0
        n = len(nums)
        
        self.total = 0
        bin = 1
        tmp = [0 for _ in range(n)]
        while bin < n:
            m = n // (2 * bin)
            if n % (2 * bin) != 0 : m += 1
            for i in range(m):
                self.mergeSort(nums, 2 * i * bin  , 2 * i * bin + bin, n, tmp)
            bin = bin * 2
        
        # if bin//2 < n:
        self.mergeSort(nums, 0  , bin//2, n, tmp)
        return self.total
    
    def mergeSort(self, nums, begin1, begin2, n, tmp):
        end1 = min(begin2, n)
        end2 = min(2 * begin2 - begin1, n)
        tmpNum = end2 - begin1
        cur = begin1
        while begin1 < end1 and begin2 < end2:
            if nums[begin1] > nums[begin2]:
                self.total += end1 - begin1
                tmp[cur] = nums[begin2]
                begin2 += 1
            else:
                tmp[cur] = nums[begin1]
                begin1 += 1
            cur += 1
                # if len(tmp1), nums keep the tmp2
        while begin1 < end1:
            tmp[cur] = nums[begin1]
            cur += 1
            begin1 += 1
        while begin2 < end2:
            tmp[cur] = nums[begin2]
            cur += 1
            begin2 += 1
        for i in range(tmpNum):
            nums[end2 - i - 1] = tmp[end2 - i - 1]

    def reversePairs2(self, nums) -> int:
        if len(nums) < 2:return 0
        n = len(nums)
        
        self.total = 0
        tmp = [0 for _ in range(n)]
        self.mergeSort2(nums, 0, n-1, tmp)
        return self.total
    

    def mergeSort2(self, nums, left, right, tmp):
        if left < right:
            center = (left + right) // 2
            self.mergeSort2(nums, left, center, tmp)
            self.mergeSort2(nums, center+1, right, tmp)
            self.merge(nums, left, center + 1, right, tmp)
    
    def merge(self, nums, leftPos, rightPos, rightEnd, tmp ):
        leftEnd = rightPos - 1
        tmpPos = leftPos
        numElements = rightEnd - leftPos + 1
        while leftPos <= leftEnd and rightPos <= rightEnd:
            if nums[leftPos] > nums[rightPos]:
                tmp[tmpPos] = nums[rightPos]
                tmpPos += 1
                rightPos += 1
                self.total += leftEnd - leftPos + 1
            else:
                tmp[tmpPos] = nums[leftPos]
                tmpPos += 1
                leftPos += 1
        while leftPos <= leftEnd:
            tmp[tmpPos] = nums[leftPos]
            tmpPos += 1
            leftPos += 1

        while rightPos <= rightEnd:
            tmp[tmpPos] = nums[rightPos]
            tmpPos += 1
            rightPos += 1
        for i in range(numElements):
            nums[rightEnd-i] = tmp[rightEnd-i]

       

if __name__ == "__main__":
    sol = Solution()
    # nums = [7,5,6,4]
    import random
    nums = [random.randint(1,20000) for _ in range(1234)]
    nums2 = nums.copy()
    from datetime import datetime
    begin = datetime.now()
    print(sol.reversePairs2(nums))
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    print(sol.reversePairs(nums2))
    
