class Solution:
    def calculate(self, s: str) -> int:
        # '_' is unitary substract
        opreates = ('+', '-', '(', ')', '_')

        stack_opr = []
        stack_opd = []
        
        def precedence(op1:str, op2:str) -> int:
            '''
             1: op1 > op2, pop from and calculate
             0: op1 == op2, pop operate
            -1: op1 < op2, push oprreate to stack
            '''
            if  op2 == '(':
                return -1
            if op1 == '(' and op2 == ")":
                return 0
            if op1 in ['+', '-' , '_'] and op2 in ['+', '-', ')']:
                return 1

        def caculate():
            op = stack_opr.pop(-1)
            op2 = stack_opd.pop(-1)
            if op == "_":
                stack_opd.append(-op2)
            elif op == '+':
                stack_opd[-1] += op2
            else:
                stack_opd[-1] -= op2            

        s = s.replace(' ', '')
        prev = 0
        words = []
        for i in range(len(s)):
            if s[i] in opreates:
                if i - prev > 0: words.append(s[prev:i])
                words.append(s[i])
                prev = i + 1
        if len(s) > prev : words.append(s[prev:])
        
        for i in range(len(words)):
            if words[i] in opreates:
                while stack_opr and precedence(stack_opr[-1], words[i]) == 1:
                    caculate()
                if stack_opr and precedence(stack_opr[-1], words[i]) == 0:
                    stack_opr.pop(-1)
                else:
                    # stack is null or precedence(stack_opr[-1], words[i]) == -1
                    if words[i] == "-" and (i == 0 or words[i-1] == "("):
                        # unitray substract
                        stack_opr.append("_")
                    else:
                        stack_opr.append(words[i])
            else:
                stack_opd.append(int(words[i]))

        while stack_opr:
            caculate()

        return stack_opd[0]

if __name__ == "__main__":
    sol = Solution()
    s = "1 + 1"
    s = "(1+(4+5+2)-3)+(6+8)"
    print(sol.calculate(s))
