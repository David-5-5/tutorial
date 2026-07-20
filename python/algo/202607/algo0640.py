class Solution:
    def solveEquation(self, equation: str) -> str:
        x_coff, val, left, sign = 0, 0, True, 1
        l = 0
        for r, ch in enumerate(equation+"+"):
            if ch == 'x':
                x_coff += (sign if left else -1 * sign) * (int(equation[l:r]) if r > l else 1)
                l = r + 1
            elif '0' <= ch <= '9': continue
            else:
                val += (-1 * sign if left else sign) * (int(equation[l:r]) if r > l else 0)
                if ch == '+': sign = 1; l = r + 1
                elif ch == '-': sign = -1; l= r + 1
                else : l = r + 1; left = False; sign = 1 # ch == '='
        
        if x_coff == 0 and val == 0:
            return "Infinite solutions"
        elif x_coff == 0 and val != 0 or val % x_coff:
            return "No solution"
        else: return "x=" + str(val//x_coff)


if __name__ == '__main__':
    sol = Solution()
    print(Solution().solveEquation("2x+3x-6x=x+2"))