def counting(nums, limit):
    counts = [0] * limit
    for val in nums:
        counts[val-1] += 1
    

    nums = []
    for i in range(limit):
        nums.extend([i + 1] * counts[i])

    return nums

if __name__ == "__main__":
    import random
    n = 1000
    nums1 = [random.randint(1,2000) for _ in range(n)]
    nums2 = nums1.copy()

    nums1 = counting(nums1, 2000)
    nums2.sort()

    for i in range(len(nums1)):
        if nums1[i] != nums2[i]:
            print("counting wrong")
            break
            
    # compare performance
    n = 5000000
    nums1 = [random.randint(1,500) for _ in range(n)]
    nums2 = nums1.copy()

    from datetime import datetime
    begin = datetime.now()
    nums2.sort()
    print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    nums1 = counting(nums1, 500)
    print((datetime.now()- begin).total_seconds())
            


    
