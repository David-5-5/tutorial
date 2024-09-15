from typing import List


class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        prev, n = nums[0], len(nums)
        st0, st1 = [],[] # 非递减 对应于每个 result[i] max(len(st)) 即是操作次数
        ans = 0
        for i in range(1, n):
            if prev <= nums[i]:
                st1.clear()
                prev = nums[i]
            else:   
                if st1 and st1[-1] > nums[i]:
                    if len(st0) == 0:
                        st0 = st1
                    else:
                        if len(st0) >= len(st1):
                            for i in range(len(st1)):
                                if st1[i] > st0[-1]:
                                    st0.extend(st1[i:len(st1)])
                                    break
                        else:
                            st0 = st1
                    st1 = []
                st1.append(nums[i])
                ans = max(ans, len(st1))
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [1682,63,124,147,897,1210,1585,1744,1764,1945,323,984,1886,346,481,1059,1388,1483,1516,1842,1868,1877,504,1197,785,955,970,1848,1851,398,907,995,1167,1214,1423,1452,1464,1474,1311,1427,1757,1992,57,1625,1260,700,725]
    print(sol.totalSteps(nums))