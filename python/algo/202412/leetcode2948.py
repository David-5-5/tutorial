from typing import List

# 周赛 373
class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        # 自行解答
        # 从小到大排序后分组，将相隔不超过 limit 的数及下标分在一组，
        # 然后按照分组所在的下标从小到大写入结果数组中
        n = len(nums)
        ans = [0] * n
        nums.append(10**10) # 哨兵
        val, inx = [], []
        for i, v in sorted(enumerate(nums), key=lambda p:p[1]):
            if val and  v - val[-1]  > limit:
                inx.sort() # 将下标排序，val 已有序
                for i_s, v_s in zip(inx, val):
                    ans[i_s] = v_s
                val, inx = [], []
            
            val.append(v)
            inx.append(i)

        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.lexicographicallySmallestArray([1,5,3,9,8], 2))