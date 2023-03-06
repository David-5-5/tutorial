class Solution:
    def kMirror(self, k: int, n: int) -> int:
        def isPalindrome(x: int) -> bool:
            tok = []
            while x:
                tok.append(x % k)
                x //= k
            return tok == tok[::-1]

        ret = 0
        begin = 0
        end = 1
        count = 0
        while count < n:
            for i in [0, 1]:
                for left in range(begin, end):
                        for mid in range(10 if i else 1):
                            if left:
                                strl = str(left)
                                value = int(strl + (str(mid) if i else '') + strl[::-1])
                            else:
                                value = mid
                            if value and isPalindrome(value) :
                                count += 1
                                ret += value
                                if count == n: return ret
                        
            begin = end
            end *= 10

    def kMirror2(self, k: int, n: int) -> int:
        '''
        Official Solution
        '''
        def isPalindrome(x: int) -> bool:
            digit = list()
            while x:
                digit.append(x % k)
                x //= k
            return digit == digit[::-1]

        left, cnt, ans = 1, 0, 0
        while cnt < n:
            right = left * 10
            # op = 0 表示枚举奇数长度回文，op = 1 表示枚举偶数长度回文
            for op in [0, 1]:
                # 枚举 i'
                for i in range(left, right):
                    if cnt == n:
                        break
                    
                    combined = i
                    x = (i // 10 if op == 0 else i)
                    while x:
                        combined = combined * 10 + x % 10
                        x //= 10
                    if isPalindrome(combined):
                        cnt += 1
                        ans += combined
            left = right


if __name__ == "__main__":
    sol = Solution()
    k, n = 2, 5 # expect 25
    # k, n = 3, 7 # expect 499
    # k, n = 7, 17  # expect 20379000
    k, n = 2, 8 # expect 470
    print(sol.kMirror2(k, n))
