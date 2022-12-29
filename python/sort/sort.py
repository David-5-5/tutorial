def verify(msg: str, nums1, nums2) -> bool:
    for i, j in zip(nums1, nums2):
        if i != j:
            print(f"{msg} is wrong!")
            return False
    return True

class Sort:
    def insertSort(self, nums):
        n = len(nums)

        for i in range(1, n):
            for j in range(i, 0, -1):
                if nums[j] < nums[j-1]:
                    nums[j], nums[j-1] = nums[j-1], nums[j]
        return nums

    def shellSort(self, nums):
        sedgewick = [1, 5, 19, 41, 109, 209, 505, 929, 2161,
                   3905, 8929, 16001, 36289, 64769, 146305,
                   260609, 587521, 1045505, 2354689, 4188161,
                   9427969, 16764929, 37730305, 67884289,
                   150958081, 268386305, 603906049, 1073643521]
        n = len(nums)
        i, keeper = 0, 0
        while i < 28:
            if sedgewick[i] > n:
                keeper = i - 1
                break
            i += 1

        while keeper >= 0:
            i = sedgewick[keeper]
            j = i
            while j < n:
                p = j
                tmp = nums[p]

                while p > 0 and nums[p - i] > tmp:
                    nums[p] = nums[p - i]
                    p -= i
                nums[p] = tmp
                j += 1
            keeper -= 1

if __name__ == '__main__':
    sort = Sort()
    import random, copy
    nums = [random.randint(1,20000) for _ in range(10 ** 3)]
    numsc = copy.deepcopy(nums)
    from datetime import datetime
    begin = datetime.now()
    nums.sort()
    print(f"python sort duration for 10 ** 3: {(datetime.now()- begin).total_seconds()}")
    begin = datetime.now()
    sort.insertSort(numsc)
    print(f"insert sort duration for 10 ** 3: {(datetime.now()- begin).total_seconds()}")
    verify("insert sort", nums, numsc)


    nums = [random.randint(1,20000) for _ in range(10 ** 5)]
    numsc = copy.deepcopy(nums)
    begin = datetime.now()
    nums.sort()
    print(f"python sort duration for 10 ** 5: {(datetime.now()- begin).total_seconds()}")
    begin = datetime.now()
    sort.shellSort(numsc)
    print(f"shell sort duration for 10 ** 5: {(datetime.now()- begin).total_seconds()}")
    verify("shell sort", nums, numsc)