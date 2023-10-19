class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        n_str = str(n)
        n_len = len(n_str)

        # Return digit beginning
        # If bit is 1st, the digit is 1~9
        # If bit is subsequeent,  the digit is 0~9
        def count(digit:int, prefix: str):
            ret = 0
            new_pre = prefix + str(digit)
            if new_pre < n_str[0:len(new_pre)]:
                ret = 1
                for i in range(1, n_len-len(prefix)):
                    ret += 10 ** i
            elif new_pre == n_str[0:len(new_pre)]:
                ret = 1
                for i in range(1, n_len-len(prefix)-1):
                    ret += 10 ** i
                if len(n_str) > len(new_pre):ret += 1 + int(n_str[len(new_pre):])
            else:
                for i in range(0, n_len-len(prefix)-1):
                    ret += 10 ** i
            return ret
        
        prefix = ''
        cnt = k
        while cnt:
            cur_cnt, pre_cnt = 0, 0
            for i in range(10):
                if prefix == '' and i == 0:
                    continue
                pre_cnt = cur_cnt
                cur_cnt += count(i, prefix)
                if cur_cnt >= cnt:break
            if cur_cnt == cnt:
                prefix += str(i)
                if prefix < n_str[0:len(prefix)]:
                    prefix = prefix.ljust(n_len, '9')
                elif prefix == n_str[0:len(prefix)]:
                    prefix = n_str
                else:
                    prefix = prefix.ljust(n_len-1, '9')
                cnt = 0
            else:
                cnt -= pre_cnt
                prefix += str(i)
                cnt -= 1
        
        return int(prefix)

if __name__ == "__main__":
    sol = Solution()
    print(sol.findKthNumber(10000, 5))