class Solution:
    def cuttingBamboo(self, bamboo_len: int) -> int:
        mod = 10**9 + 7 
        ans = 1
        # 遍历分割段数k，从2到bamboo_len
        for k in range(2, bamboo_len + 1):
            frac = bamboo_len // k  # 整除结果（对应C++的/）
            rem = bamboo_len % k    # 余数
            res = 1
            # 计算rem个(frac+1)的乘积
            for _ in range(rem):
                res *= (frac + 1)
            # 计算(k-rem)个frac的乘积
            for _ in range(k - rem):
                res *= frac
            if res <= ans:
                break
            else:
                ans = res
        return ans % mod

    def cuttingBamboo2(self, bamboo_len: int) -> int:
        mod = 10**9 + 7 
        ans = 1
        
        for k in range(2, bamboo_len + 1):
            tot = bamboo_len
            res = 1
            while tot:
                div = (tot + k - 1) // k    # CONCRETE MATH gropus PAGE 97
                res *= div
                tot -= div
                k -= 1
            if res <= ans: break
            else: ans = res 
        return ans % mod   
    
    def cuttingBamboo3(self, bamboo_len: int) -> int:
        dp = [0] * (bamboo_len + 1)
        dp[0], dp[1] = 1, 1
        
        # 遍历每个长度i，从2到bamboo_len
        for i in range(2, bamboo_len + 1):
            # 遍历分割出的第一段长度len，从i-1递减到1
            len = i - 1
            while len > 0:
                current = max(dp[i - len], i - len) * len
                if current > dp[i]:
                    dp[i] = current
                len -= 1
        
        return dp[bamboo_len] % (10 ** 9 + 7)