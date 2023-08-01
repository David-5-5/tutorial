class Solution:
    def superpalindromesInRange(self, left: str, right: str) -> int:
        ans = 0

        def isPalindromes(s: str):
            n = len(s)
            for i in range(0, n//2):
                if s[i] != s[n - i - 1]:
                    return False
            return True

        for l in range(1, 10):
            mid = l % 2 # The len of mid digit
            pre = l // 2 # The len of left digit

            if pre == 0:
                for i in range(0, mid * 10):
                    val = i * i
                    if val > int(right):
                        return ans
                    if int(left) <=val and isPalindromes(str(val)):
                        ans += 1
            else:
                begin = int("1".ljust(pre,'0'))
                for j in range(begin, begin * 10):
                    if mid == 0:
                        pal = str(j) + str(j)[::-1]
                        val = int(pal) ** 2
                        if val > int(right):
                            return ans
                        if int(left) <=val and isPalindromes(str(val)):
                            ans += 1
                    else:
                        for s in range(0, 10):
                            pal = str(j) + str(s) + str(j)[::-1]
                            val = int(pal) ** 2
                            if val > int(right):
                                return ans
                            if int(left) <=val and isPalindromes(str(val)):
                                ans += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.superpalindromesInRange('4', '999999999999999999'))