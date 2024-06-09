from functools import lru_cache
class Solution:
    def findGoodStrings(self, n: int, s1: str, s2: str, evil: str) -> int:
        MOD = 10 ** 9 + 7

        p_pi = [0] * len(evil)
        # Compute the prefix function of p
        for i in range(1, len(evil)):
            j = p_pi[i-1]
            while j>0 and evil[j] != evil[i]: j = p_pi[j-1]
            if evil[j] == evil[i]:
                p_pi[i] = j+1
            else:
                p_pi[i] = j

        @lru_cache(maxsize = None)
        def f(i: int, is_left:bool , is_right: bool, pre: int) -> int:
            if i == n:
                return 1  # 合法序列
            res = 0

            a_ord = ord('a')
            
            low = ord(s1[i]) - a_ord if is_left else 0  
            up = ord(s2[i]) - a_ord if is_right else 25  
            
            for d in range(low, up + 1):
                new_pre = pre
                while new_pre > 0 and d != ord(evil[new_pre]) - a_ord:
                    new_pre=p_pi[new_pre-1]
                if d == ord(evil[pre]) - a_ord:
                    new_pre += 1
                if new_pre == len(evil):
                    continue
                res += f(i+1, is_left and d == low, is_right and d == up, new_pre) % MOD

            return res % MOD
        return f(0, True, True, 0)


if __name__ == "__main__":
    sol = Solution()
    # n, s1, s2, evil = 2, "aa", "da", "b"
    n, s1, s2, evil = 8, "pzdanyao", "wgpmtywi", "sdka"
    print(sol.findGoodStrings(n, s1, s2, evil))