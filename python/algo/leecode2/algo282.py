class Solution:

    def addOperators(self, num: str, target: int):
        multi = "*"
        add = "+"
        sub = "-"
        # concate two digit
        con = "|"

        def calculate(stack) -> int:
            opd2, op, opd1 = int(stack.pop(-1)), stack.pop(-1), int(stack.pop(-1))

            if op == multi:
                stack.append(opd1 * opd2)
            if op == add:
                stack.append(opd1 + opd2)
            if op == sub:
                stack.append(opd1 - opd2)
            if op == con:
                stack.append(opd1 * 10 + opd2)

        # If return True, pop op1 from prev to calcuate
        # If return False, push op2 into stack
        def precedence(op1:str, op2:str) -> bool:
            if op1 == con:
                return True
            if op1 == multi and op2 == con:
                return False
            elif op1 == multi:
                return True
            if op1 in [add, sub] and op2 in [add,sub]:
                return True
            if op1 in [add, sub] and op2 in [multi, con]:
                return False


        n = len(num)
        if n == 1:
            if int(num) == target:
                return [num]
            else:
                return []
        
        ret = []
        ops = [(num, [])]
        while ops:
            cur, stack = ops.pop(0)
            if len(cur) == 2*n - 1:
                stack.append(cur[2*n-2])
                while len(stack) > 1:
                    calculate(stack)
                if stack[0] == target:
                    ret.append(cur)
                continue

            inx = (len(cur) - n) * 2
            for op in [multi, add, sub, con]:
                if stack and stack[-1] != con and op == con and cur[inx]=='0':continue
                if not stack and op == con and cur[inx]=='0':continue

                t_stack = stack.copy()
                if t_stack and  precedence(t_stack[-1], op):
                        t_stack.append(cur[inx])
                        calculate(t_stack)
                        t_stack.append(op)
                else:
                    t_stack.append(cur[inx])
                    t_stack.append(op)

                ops.append((cur[0:inx+1] + op + cur[inx+1:], t_stack))

        return ret


    def addOperators2(self, num: str, target: int):
        multi = "*"
        add = "+"
        sub = "-"
        # concate two digit
        con = "|"
        empty = ""

        def calculate(op: str, opd1: int, opd2: int) -> int:
            if op == multi:
                return opd1 * opd2
            if op == add:
                return opd1 + opd2
            if op == sub:
                return opd1 - opd2
            if op == con:
                return opd1 * 10 + opd2

        # If return True, pop op1 from prev to calcuate
        # If return False, push op2 into stack
        def precedence(op1:str, op2:str) -> bool:
            if op1 == empty:
                return False
            if op2 == empty:
                return True
            if op1 == con:
                return True
            if op1 == multi and op2 == con:
                return False
            elif op1 == multi:
                return True
            if op1 in [add, sub] and op2 in [add,sub]:
                return True
            if op1 in [add, sub] and op2 == multi:
                return False


        def combine(operands: str ,operates: str):
            comb = operands[0]
            for i in range(len(operates)):
                comb += (operates[i] if operates[i]!=con else "") + operands[i+1]
            return comb

        n = len(num)
        if n == 1:
            if int(num) == target:
                return [num]
            else:
                return []
        
        ops = [""]
        while len(ops[0]) < n-1:
            cur = ops.pop(0)
            ops.append(cur+multi)
            ops.append(cur+add)
            ops.append(cur+sub)
            ops.append(cur+con)
        
        ret = []
        while ops:
            inx = 0
            stack_opd = [int(num[0])]
            stack_opr = []
            operate = ops.pop(0)
            while inx <= len(operate):
                while precedence(stack_opr[-1] if stack_opr else empty, operate[inx] if inx<len(operate) else empty):
                    op2 = stack_opd.pop(-1)
                    op1 = stack_opd.pop(-1)
                    op = stack_opr.pop(-1)
                    result = calculate(op, op1, op2)
                    stack_opd.append(result)
                if inx < len(operate) :
                    stack_opr.append(operate[inx])
                    stack_opd.append(int(num[inx+1]))
                inx += 1
            if stack_opd[0] == target:
                ret.append(combine(num, operate))

        return ret


if __name__ == "__main__":
    sol = Solution()
    num, target = "123", 6
    num, target = "105", 5
    # num, target = "3456237490", 9191
    print(sol.addOperators(num, target))