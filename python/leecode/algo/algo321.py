# extract t number from nums , and left is max of len(nums) - t 
def extract(nums, t):
    if t == 0: return nums
    if t == len(nums):return []
    ret = []
    cur = 0
    ret.append(nums[0])
    cur += 1
    pops = 0
    while cur < len(nums):
        while ret and ret[-1] < nums[cur] and pops < t:
            ret.pop(-1)
            pops += 1
        if pops == t:
            ret = ret + nums[cur:]
            return ret
        ret.append(nums[cur])
        cur += 1
    return ret if len(ret) == len(nums) - t else ret[0:len(nums)-t]

def combine(nums1, nums2):
    ret = []
    cur1 , cur2 = 0, 0
    while cur1<len(nums1) and cur2 < len(nums2):
        if nums1[cur1] > nums2[cur2]:
            ret.append(nums1[cur1])
            cur1 += 1
        elif nums1[cur1] == nums2[cur2]:
            i = 1
            while cur1 + i < len(nums1) and cur2 + i < len(nums2) and nums1[cur1+i] == nums2[cur2+i]:
                i += 1
            if cur1 + i < len(nums1) and cur2 + i < len(nums2):
                if nums1[cur1+i] > nums2[cur2+i]:
                    ret.append(nums1[cur1])
                    cur1 += 1
                else:
                    ret.append(nums2[cur2])
                    cur2 += 1
            elif cur1 + i < len(nums1):
                ret.append(nums1[cur1])
                cur1 += 1
            else:
                ret.append(nums2[cur2])
                cur2 += 1
        else:
            ret.append(nums2[cur2])
            cur2 += 1
    if cur1 < len(nums1) :
        ret = ret + nums1[cur1:]
    if cur2 < len(nums2):
        ret = ret + nums2[cur2:]
    return ret

class Solution:
    def maxNumber(self, nums1, nums2, k: int) :
        maxNum = [0]
        n = len(nums1)
        m = len(nums2)
        if m + n == k : return combine(nums1, nums2)

        ext = m + n - k

        for i in range(ext + 1):
            if i <= n and ext-i <= m:
                ex1 = extract(nums1, i)
                ex2 = extract(nums2, ext - i)
                com = combine(ex1, ex2)
                if int("".join([str(x) for x in com])) > int("".join([str(x) for x in maxNum])):
                    maxNum = com
        return maxNum

if __name__ == "__main__":
    sol = Solution()
    # nums1 = [3,4,6,5]
    # nums2 = [9,1,2,5,8,3]
    nums1 = [3,9]
    nums2 = [8,9]
    # nums1 = [8,6,9]
    # nums2 = [1,7,5]
    # nums1 = [2,5,6,4,4,0]
    # nums2 = [7,3,8,0,6,5,7,6,2]
    print(sol.maxNumber(nums1, nums2, 3))