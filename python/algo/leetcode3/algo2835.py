from typing import Counter, List

# 周赛 360
class Solution:
    # Refer to https://leetcode.cn/circle/discuss/CaOJ45/
    # https://leetcode.cn/problems/minimum-operations-to-form-subsequence-with-target-sum/solutions/2413344/tan-xin-by-endlesscheng-immn/
    def minOperations(self, nums: List[int], target: int) -> int:
        # 参考题解
        if sum(nums) < target:return -1

        cnt = Counter(nums)
        ans = s = i = 0
        while 1 << i <= target:
            s += cnt[1<<i] << i
            mask = (1<<(i+1)) - 1
            i += 1
            if s >= target & mask:
                continue

            ans += 1
            while cnt[1<<i] == 0:
                i += 1
                ans += 1

        return ans


    def minOperations2(self, nums: List[int], target: int) -> int:
        # 自行解答
        if sum(nums) < target: return -1

        cnt = Counter(nums)
        
        ans = 0
        for i in range(31):
            if target >> i & 1:
                found = False
                if cnt[1<<i]:
                    cnt[1<<i] -= 1
                    found = True
                else:
                    # 找最近的值分解
                    for j in range(i, 31):
                        if cnt[1<<j]:
                            cnt[1<<j] -= 1
                            ans += j - i # 需要分解的次数
                            found = True
                            break
                        else: cnt[1<<j] += 1 # 过程中路过的每个值加1
                        # cnt[1<<i] 实际上是2,需要用掉一个
                if not found: return -1
            # 将当前未用掉的值合并到高位
            acc = cnt[1<<i] // 2
            cnt[1<<(i+1)] += acc
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.minOperations([1,32,1,2],12))
    print(sol.minOperations2([1,32,1,2],12))
