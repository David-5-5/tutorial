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

    def calculate2(self, s: str) -> int:
        # 2025.5 复习，用栈简化实现，不需要递归
        # st 存储操作数, op 存储操作符
        # - 作为一元运算 和 二元运算
        s = s.replace(' ', '')
        if s[0] == '-': s = "0" + s
        elif s[0] == '(': s = "0+" + s
        st, op = [], []

        s = s.replace('(-', '(0-')
        val, depth = None, 1
        def push():
            nonlocal val
            if val is not None: st.append(val)
            while len(st) > depth:
                opr = op.pop()
                op1 = st.pop()
                if opr == '+':
                    st[-1]  += op1
                else: st[-1] -= op1

        for ch in s:
            if ch.isdigit():
                if val is None:val = 0
                val = val * 10 + int(ch)
            else:
                if ch in ('+', '-'):
                    push()
                    op.append(ch)
                elif ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                    push()
                val = None     

        if val is not None or len(st) > 1:push()
        return st[0]
    
    
if __name__ == "__main__":
    sol = Solution()
    s = "0"
    # s = "(1+(4+5+2)-3)+(6+8)"
    print(sol.calculate(s))
    print(sol.calculate2(s))
