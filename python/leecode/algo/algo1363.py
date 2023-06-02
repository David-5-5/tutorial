class Solution:
    def largestMultipleOfThree(self, digits) -> str:
        zeros, ones, twos  = [], [], []
        onedel, twodel = 0, 0
        onerem, tworem = 0, 0
        
        for digit in digits:
            remainder = digit % 3
            if remainder == 0:
                zeros.append(digit)
            elif remainder == 1:
                ones.append(digit)
            else:
                twos.append(digit)

        onerem = len(ones) % 3
        tworem = len(twos) % 3

        if (onerem == 1 and tworem == 0) or (onerem == 2 and tworem == 1):
            onedel = 1
        elif (onerem == 0 and tworem == 1) or (onerem == 1 and tworem == 2):
            twodel = 1
        elif onerem == 0 and tworem == 2:
            if len(onerem) > 0:
                onedel = 1
            else:
                twodel = 2
        elif onerem == 2 and tworem == 0:
            if len(onerem) > 0:
                twodel = 2
            else:
                onedel = 1

        ret = []
        ret.extend(zeros)

        ones.sort()
        twos.sort()

        for _ in range(onedel):
            ones.pop(0)
        for _ in range(twodel):
            twos.pop(0)

        ret.extend(ones)
        ret.extend(twos)
        ret.sort(reverse=True)
        retStr = [str(x) for x in ret]
        result = ''.join(retStr)

        if len(result) > 1 and result[0] == '0':
            return 0
        else:
            return result


if __name__ == "__main__":
    sol = Solution()
    digits = [8,1,9]
    print(sol.largestMultipleOfThree(digits))
    


        