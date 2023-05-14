###############################################################################
# Python3 program
# Common methods for SORT ALGORITHM
###############################################################################
def verify(msg: str, nums1, nums2) -> bool:
    for i, j in zip(nums1, nums2):
        if i != j:
            print(f"{msg} is wrong!")
            return False
    return True

# This function sorts array from left index to
# to right index which is of size atmost RUN
def _insertSort(arr, left, right):
    for i in range(left + 1, right + 1):
        j = i
        while j > left and arr[j] < arr[j - 1]:
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
            j -= 1

maxRandom = 20000

def execSort(func, num):
    import random, copy
    nums = [random.randint(1,maxRandom) for _ in range(num)]
    numsc = copy.deepcopy(nums)
    from datetime import datetime
    begin = datetime.now()
    nums.sort()
    print(f"python sort duration for {num}: {(datetime.now()- begin).total_seconds()}")
    begin = datetime.now()
    func(numsc)
    print(f"{func} duration for {num}: {(datetime.now()- begin).total_seconds()}")
    verify(f"{func}", nums, numsc)


###############################################################################
# Python3 program to perform INSERT SORT
###############################################################################
def insertSort(nums):
    n = len(nums)

    return _insertSort(nums, 0, n-1)


###############################################################################
# Python3 program to perform SHELL SORT
###############################################################################
def shellSort(nums):
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


###############################################################################
# Python3 program to perform HEAP SORT
###############################################################################
def heapify(nums, n:int, i:int):
    """
    Internal method for heapsort that is used in deletemax and buildHeap
    nums, an array of comparable item
    i, the position from which to percollate down
    n, the logical size of the binary heap
    """
    largest = i  # Initialize largest as root
    l = 2 * i + 1  # left = 2*i + 1
    r = 2 * i + 2  # right = 2*i + 2
 
    # See if left child of root exists and is
    # greater than root
 
    if l < n and nums[i] < nums[l]:
        largest = l
 
    # See if right child of root exists and is
    # greater than root
    if r < n and nums[largest] < nums[r]:
        largest = r
 
    # Change root, if needed
 
    if largest != i:
        (nums[i], nums[largest]) = (nums[largest], nums[i])  # swap
        # Heapify the root.
        heapify(nums, n, largest)


def heapSort(nums):
    n = len(nums)
    
    for i in range(n // 2 - 1, -1, -1):
        heapify(nums, n, i)
    
    for i in range(n - 1, 0, -1):
        (nums[i], nums[0]) = (nums[0], nums[i])  # swap
        heapify(nums, i, 0)


###############################################################################
# Python3 program to perform merge sort
###############################################################################
def _merge(nums, leftPos, rightPos, rightEnd, tmp ):
    leftEnd = rightPos - 1
    tmpPos = leftPos
    numElements = rightEnd - leftPos + 1
    while leftPos <= leftEnd and rightPos <= rightEnd:
        if nums[leftPos] > nums[rightPos]:
            tmp[tmpPos] = nums[rightPos]
            tmpPos += 1
            rightPos += 1
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


def _mergeSort(nums, left, right, tmp):
    if left < right:
        center = (left + right) // 2
        _mergeSort(nums, left, center, tmp)
        _mergeSort(nums, center+1, right, tmp)
        _merge(nums, left, center + 1, right, tmp)

def mergeSort(nums):
    n = len(nums)
    tmp = [0 for _ in range(n)]
    _mergeSort(nums, 0, n-1, tmp)

###############################################################################
# Python3 program to perform basic timSort
###############################################################################
MIN_MERGE = 32

def calcMinRun(n):
    """Returns the minimum length of a
    run from 23 - 64 so that
    the len(array)/minrun is less than or
    equal to a power of 2.
 
    e.g. 1=>1, ..., 63=>63, 64=>32, 65=>33,
    ..., 127=>64, 128=>32, ...
    """
    r = 0
    while n >= MIN_MERGE:
        r |= n & 1
        n >>= 1
    return n + r

 
# Merge function merges the sorted runs
def merge(arr, l, m, r):
 
    # original array is broken in two parts
    # left and right array
    len1, len2 = m - l + 1, r - m
    left, right = [], []
    for i in range(0, len1):
        left.append(arr[l + i])
    for i in range(0, len2):
        right.append(arr[m + 1 + i])
 
    i, j, k = 0, 0, l
 
    # after comparing, we merge those two array
    # in larger sub array
    while i < len1 and j < len2:
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
 
        else:
            arr[k] = right[j]
            j += 1
 
        k += 1
 
    # Copy remaining elements of left, if any
    while i < len1:
        arr[k] = left[i]
        k += 1
        i += 1
 
    # Copy remaining element of right, if any
    while j < len2:
        arr[k] = right[j]
        k += 1
        j += 1
 
 
# Iterative Timsort function to sort the
# array[0...n-1] (similar to merge sort)
def timSort(arr):
    n = len(arr)
    minRun = calcMinRun(n)
 
    # Sort individual subarrays of size RUN
    for start in range(0, n, minRun):
        end = min(start + minRun - 1, n - 1)
        _insertSort(arr, start, end)
 
    # Start merging from size RUN (or 32). It will merge
    # to form size 64, then 128, 256 and so on ....
    size = minRun
    while size < n:
 
        # Pick starting point of left sub array. We
        # are going to merge arr[left..left+size-1]
        # and arr[left+size, left+2*size-1]
        # After every merge, we increase left by 2*size
        for left in range(0, n, 2 * size):
 
            # Find ending point of left sub array
            # mid+1 is starting point of right sub array
            mid = min(n - 1, left + size - 1)
            right = min((left + 2 * size - 1), (n - 1))
 
            # Merge sub array arr[left.....mid] &
            # arr[mid+1....right]
            if mid < right:
                merge(arr, left, mid, right)
 
        size = 2 * size



if __name__ == '__main__':

    # num = 1 << 11
    # execSort(insertSort, num)

    num = 1 << 18
    # execSort(shellSort, num)

    execSort(heapSort, num)

    execSort(mergeSort, num)

    execSort(timSort, num)