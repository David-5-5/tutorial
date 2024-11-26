from typing import List

# 贪心专题 双序列配对
class Solution:
    def advantageCount(self, nums1: List[int], nums2: List[int]) -> List[int]:
        # 自行解答 排序 + 指针遍历
        n = len(nums1)
        ans = [-1] * n
        tail = []
        inx = 0
        nums1.sort()
        for i, v in sorted(enumerate(nums2), key=lambda p:p[1]):
            while inx < n and nums1[inx] <= v:
                tail.append(nums1[inx])
                inx += 1
            if inx == n: break
            ans[i] = nums1[inx]
            inx += 1
        for i in range(n):
            if ans[i] == -1:
                ans[i] = tail.pop()
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2 = [2,7,11,15], [1,10,4,11]
    print(sol.advantageCount(nums1, nums2))