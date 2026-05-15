# 五、思维题 - 5.5 贡献法
class Solution:
    def sumOfNumbers(self, l: int, r: int, k: int) -> int:
        # 自行解答 
        # 根据每个数在每位出现的出现得出和为
        #   (r-l+1)^{k-1} * sum(l..r) * (10^{k-1} + 10^{k-2} + ... + 1)
        # = (r-l+1)^{k-1} * ((l+r) * (r-l+1) / 2) * (10^k-1) * (9^{-1}) % mod
        mod = 10 ** 9 + 7
        inv_9 = pow(9, mod-2, mod)

        ans = pow(r - l + 1, k-1, mod) * ((l + r) * (r - l + 1) // 2)% mod
        ans = ans * (pow(10, k, mod) - 1) % mod

        return ans * inv_9 % mod  
