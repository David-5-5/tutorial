import heapq
class Solution:
    def maximumANDSum(self, nums, numSlots) -> int:
        n = len(nums)
        mask_max = 3 ** numSlots

        f = [0] * mask_max        
        for mask in range(1, mask_max):
            cnt, dummy = 0, mask

            for i in range(numSlots):
                cnt += dummy % 3
                dummy //= 3
            
            if cnt > n:
                continue
            
            dummy, w = mask, 1
            for i in range(numSlots):
                has = dummy % 3
                if has > 0:
                    f[mask] = max(f[mask], f[mask - w] + (nums[cnt - 1] & (i + 1)))
                dummy //= 3
                w *= 3
        
        return max(f)


    # can't pass through all testcase
    def maximumANDSum2(self, nums, numSlots) -> int:
        n = len(nums)
        nums.sort()
        numUsed = [-1] * n
        inSlots = [0] * numSlots
        andRes = []
        ands = [[0] * numSlots for _ in range(n)]
        for i in range(n):
            for j in range(numSlots):
                ands[i][j] = nums[i] & (j+1)
                heapq.heappush(andRes, (-(nums[i] & (j+1)), i, j))
        res = 0
        while andRes:
            result, i, j = heapq.heappop(andRes)
            
            if numUsed[i] == -1:
                numUsed[i] = j
                inSlots[j] += 1
                res -= result
            elif inSlots[numUsed[i]] > 2:
                # From previous numUsed[i]'th slot to jth slot
                inSlots[numUsed[i]] -= 1
                # Add current value of '&'op
                res -= result
                # substract previous value of '&' op
                res -= ands[i][numUsed[i]]
                numUsed[i] = j
                inSlots[j] += 1

        return res

if __name__ == "__main__":
    sol = Solution()
    # expect 40
    # nums, numSlots = [14,7,9,8,2,4,11,1,9], 8
    # expect 19
    # nums, numSlots = [4,2,2,11,7,12,9,8],  4
    # expect 60
    # nums, numSlots = [8,13,3,15,3,15,2,15,5,7,6], 8
    # expect 60
    nums, numSlots = [7,6,13,13,13,6,3,12,6,4,10,3,2], 7
    print(sol.maximumANDSum(nums, numSlots))