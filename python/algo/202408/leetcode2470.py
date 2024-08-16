from collections import defaultdict
from typing import List

# 周赛 321 
class Solution:
    def subarrayLCM(self, nums: List[int], k: int) -> int:
        # 自行解答，速度快，但是代码比较乱
        factor = set()
        cnt = defaultdict(int)
        nums.append(k+1)

        i, lcm = 2, k
        while i * i <= lcm:
            if lcm % i == 0:
                c = 0
                while lcm % i == 0:
                    lcm //= i
                    c += 1
                factor.add(i**c)
            i += 1
        if lcm > 1: factor.add(lcm)
        if not factor:factor.add(k) # k == 1

        def is_lcm() -> int :
            return all(cnt[p] for p in cnt.keys())
        
        def count(l: int, r: int) -> int:
            res = 0
            for f in factor: cnt[f] = 0
            pr = ll = lr = l
            # 找 lr 端点，ll - lr 包含最小公倍数
            while lr <= r:
                for f in factor:
                    if nums[lr] % f == 0: cnt[f] += 1
                if is_lcm():
                    # ll 尽量右移
                    while ll < lr:
                        for f in factor:
                            if nums[ll] % f == 0: cnt[f] -= 1
                        if not is_lcm(): break
                        ll += 1
                    res += max((ll-pr+1),1) * max((r - lr + 1),1)
                    pr = ll = lr = ll + 1
                    for f in factor: cnt[f] = 0
                    continue
                lr += 1
            return res

        ans, l = 0, 0
        for r, num in enumerate(nums):
            if k % num != 0:
                ans += count(l, r-1)
                l = r + 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1000], 1000
    print(sol.subarrayLCM(nums, k))

