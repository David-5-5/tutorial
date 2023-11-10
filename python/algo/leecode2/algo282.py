class Solution:

    def addOperators(self, num: str, target: int):
        '''
        Use last multiple value instead of cacluate by precedence        
        '''
        n = len(num)
        
        ans = []
        # bfs array
        ops = [(0, "", 0, 0)]
        count = 0
        while ops:
            count += 1
            '''
            !!!!SOLVE THE OVERTIME!!!!!!!!!!!!!
            '''
            # inx, expr, ret, mul = ops.pop(0)
            inx, expr, ret, mul = ops.pop(-1)
            if inx == n:
                if ret == target:
                    ans.append(expr)
                continue
            
            for i in range(1, n+1-inx):
                if num[inx] == "0" and i > 1:break
                val = int(num[inx:i + inx])
                if inx == 0:
                    ops.append((i, num[inx:i + inx], val, val))
                else:
                    ops.append((i + inx, expr+"*"+num[inx:i + inx], ret - mul + mul * val, mul*val))
                    ops.append((i + inx, expr+"+"+num[inx:i + inx], ret+val, val))
                    ops.append((i + inx, expr+"-"+num[inx:i + inx], ret-val, -val))
        print(count)
        return ans


    def addOperators_recursion(self, num: str, target: int):
        '''
        The final solution:
        First, use recusion instead of bfs array, why?????????
        Secord, use last multiple value instead of cacluate by precedence
        '''
        n = len(num)
        
        ans = []
        count = 0
        def backtrack(inx, expr, ret, mul):
            nonlocal count
            count += 1
            if inx == n:
                if ret == target:
                    ans.append(expr)
                return
            
            for i in range(1, n+1-inx):
                if num[inx] == "0" and i > 1:break
                val = int(num[inx:i + inx])
                if inx == 0:
                    backtrack(i, num[inx:i + inx], val, val)
                else:
                    backtrack(i + inx, expr+"*"+num[inx:i + inx], ret - mul + mul * val, mul*val)
                    backtrack(i + inx, expr+"+"+num[inx:i + inx], ret+val, val)
                    backtrack(i + inx, expr+"-"+num[inx:i + inx], ret-val, -val)
        
        backtrack(0, "", 0, 0)
        print(count)
        return ans    

    def addOperators_original(self, num: str, target: int):
        '''
        !!!!!!!!!!!!!OVERTIME!!!!!!!!!!!!!
        '''
        multi = "*"
        add = "+"
        sub = "-"

        def calculate(stack) -> int:
            opd2, op, opd1 = int(stack.pop(-1)), stack.pop(-1), int(stack.pop(-1))

            if op == multi:
                stack.append(opd1 * opd2)
            if op == add:
                stack.append(opd1 + opd2)
            if op == sub:
                stack.append(opd1 - opd2)

        # If return True, pop op1 from prev to calcuate
        # If return False, push op2 into stack
        def precedence(op1:str, op2:str) -> bool:
            if op1 == multi:
                return True
            if op1 in [add, sub] and op2 in [add,sub]:
                return True
            if op1 in [add, sub] and op2 in [multi]:
                return False

        n = len(num)
        
        ret = []
        ops = [(0, "", [])]
        while ops:
            '''
            ops.pop(0) CHANGE TO ops.pop(-1)
            !!!!SOLVE THE OVERTIME!!!!!!!!!!!!!
            '''
            inx, expr, stack = ops.pop(-1)
            if inx == n:
                while len(stack) > 1:
                    calculate(stack)
                if stack[0] == target:
                    ret.append(expr)
                continue
            
            for i in range(1, n+1-inx):
                if num[inx] == "0" and i > 1:break
                if i == n - inx:
                    t_stack = stack.copy()
                    t_stack.append(int(num[inx:]))
                    ops.append((i + inx, expr+num[inx:i + inx], t_stack))
                    continue
                for op in [multi, add, sub]:
                    t_stack = stack.copy()
                    if t_stack and  precedence(t_stack[-1], op):
                        t_stack.append(int(num[inx:i+inx]))
                        calculate(t_stack)
                        while len(t_stack) > 1 and precedence(t_stack[-2], op):
                            calculate(t_stack)
                        t_stack.append(op)
                    else:
                        t_stack.append(num[inx:i+inx])
                        t_stack.append(op)
                    ops.append((i + inx, expr+num[inx:i + inx]+op, t_stack))
        
        return ret


    def addOperators_original_recursion(self, num: str, target: int):
        '''
        !!!!!!!!!!!!!RECURSION IS MUST!!!!!!!!!!!!
        '''        
        multi = "*"
        add = "+"
        sub = "-"

        def calculate(stack) -> int:
            opd2, op, opd1 = int(stack.pop(-1)), stack.pop(-1), int(stack.pop(-1))

            if op == multi:
                stack.append(opd1 * opd2)
            if op == add:
                stack.append(opd1 + opd2)
            if op == sub:
                stack.append(opd1 - opd2)

        # If return True, pop op1 from prev to calcuate
        # If return False, push op2 into stack
        def precedence(op1:str, op2:str) -> bool:
            if op1 == multi:
                return True
            if op1 in [add, sub] and op2 in [add, sub]:
                return True
            if op1 in [add, sub] and op2 in [multi]:
                return False

        n = len(num)
        
        ret = []
        def backtrack(inx, expr, stack):

            if inx == n:
                while len(stack) > 1:
                    calculate(stack)
                if stack[0] == target:
                    ret.append(expr)
                return
            
            for i in range(1, n+1-inx):
                if num[inx] == "0" and i > 1:break
                if i == n - inx:
                    t_stack = stack.copy()
                    t_stack.append(int(num[inx:]))
                    backtrack(i + inx, expr+num[inx:i + inx], t_stack)
                    continue
                for op in [multi, add, sub]:
                    t_stack = stack.copy()
                    if t_stack and  precedence(t_stack[-1], op):
                        t_stack.append(int(num[inx:i+inx]))
                        calculate(t_stack)
                        while len(t_stack) > 1 and precedence(t_stack[-2], op):
                            calculate(t_stack)                        
                        t_stack.append(op)
                    else:
                        t_stack.append(int(num[inx:i+inx]))
                        t_stack.append(op)
                    backtrack(i + inx, expr+num[inx:i + inx]+op, t_stack)
        
        backtrack(0, "", [])
        return ret

    def addOperators_eval(self, num: str, target: int):
        '''
        !!!!!!!!!!!!!OVERTIME!!!!!!!!!!!!!
        !!!PERFROMANCE OF EVAL IS WORST!!!
        '''
        n = len(num)
        multi, add, sub = "*", "+", "-"

        ret = []
        ops = [(0, "")]
        while ops:
            inx, expr = ops.pop(0)
            if inx == n:
                if eval(expr) == target:
                    ret.append(expr)
                continue
            
            for i in range(1, n+1-inx):
                if num[inx] == "0" and i > 1:break
                if i == n - inx:
                    ops.append((i + inx, expr+num[inx:i + inx]))
                    continue
                for op in [multi, add, sub]:
                    ops.append((i + inx, expr+num[inx:i + inx]+op))
        
        return ret

    def addOperators_eval_recursion(self, num: str, target: int):
        '''
        !!SHOULD PASS WITH BAD PERFORMANCE!!
        '''
        n = len(num)
        multi, add, sub = "*", "+", "-"

        ret = []
        def backtrack(inx, expr):
            if inx == n:
                if eval(expr) == target:
                    ret.append(expr)
                return
            
            for i in range(1, n+1-inx):
                if num[inx] == "0" and i > 1:break
                if i == n - inx:
                    backtrack(i + inx, expr+num[inx:i + inx])
                    continue
                for op in [multi, add, sub]:
                    backtrack(i + inx, expr+num[inx:i + inx]+op)
        backtrack(0, "")
        return ret

if __name__ == "__main__":
    sol = Solution()
    num, target = "123", 6
    num, target = "1054", 5
    num, target = "3456237490", 9191
    num, target = "123456789", 45
    from datetime import datetime
    # begin = datetime.now()
    # print(sol.addOperators(num, target))
    # print((datetime.now()- begin).total_seconds())

    # begin = datetime.now()
    # print(sol.addOperators_recursion(num, target))
    # print((datetime.now()- begin).total_seconds())

    # begin = datetime.now()
    # print(sol.addOperators_original(num, target))
    # print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    print(sol.addOperators_original_recursion(num, target))
    print((datetime.now()- begin).total_seconds())

    begin = datetime.now()
    print(sol.addOperators_original(num, target))
    print((datetime.now()- begin).total_seconds())