class Solution:
    def braceExpansionII(self, expression: str) :

        def cal(op:str):
            s2 = operand.pop(-1)
            s1 = operand.pop(-1)
            if op == ',':
                for e in s2:
                    if e not in s1:
                        s1.append(e)
                operand.append(s1)
            else:
                result = []
                for e1 in s1:
                    for e2 in s2:
                        if e1 + e2 not in result:
                            result.append(e1 + e2)
                operand.append(result)

        def next(inx) :
            if inx == len(expression): return '', len(expression)
            if expression[inx] in ['{', '}', ',', '.']:
                return expression[inx], inx + 1
            else:
                offset = 1
                while inx + offset < len(expression) and expression[inx + offset] not in ['{', '}', ',', '.']:
                    offset += 1
                return expression[inx:inx+offset], inx + offset
        
        def isOperator(s:str) -> bool:
            if s == '{' or s == '}' or s == ',' or s == '.' or s == '' :
                return True
            else:
                return False

        def compare(cur: str) -> int:
            '''
            The action of return
            1: > toCal 
            0: == pop
            -1: < push
            '''
            if not operator:
                return -1
            if operator[-1] == '{' and cur in ['{', ',', '.']:
                return -1
            if operator[-1] == '{' and cur == '}':
                return 0
            if operator[-1] == ',' and cur in [',', '}'] :
                return 1
            if operator[-1] == ',' and cur in ['.', '{']:
                return -1
            if operator[-1] == '.' and cur in ['.', ',', '}'] :
                return 1
            if operator[-1] == '.' and cur in ['{'] :
                return -1
            if cur == '':
                return 1

        operator = []
        operand = []
        cur = 0
        
        inx = expression.find('{')
        while inx != -1:
            if 0 <= inx -1 and expression[inx-1] not in [',','{'] :
                expression = expression[0:inx] + '.' + expression[inx:]
                inx += 1
            inx = expression.find('{', inx+1)

        inx = expression.find('}')
        while inx != -1:
            if inx+1 < len(expression) and expression[inx+1] not in [',', '.', '}'] :
                expression = expression[0:inx+1] + '.' + expression[inx+1:]
                inx += 1
            inx = expression.find('}', inx+1)

        val, cur = next(cur)
        while val != '':
            if isOperator(val):
                action = compare(val)
                while action == 1:
                    op = operator.pop(-1)
                    cal(op)
                    action = compare(val)
                if action == -1:
                    operator.append(val)
                else:
                    operator.pop(-1)
            else :
                operand.append([val])
            val, cur = next(cur)

        while operator:
            op1 = operator.pop(-1)
            cal(op1)
        
        operand[0].sort()
        return operand[0]

if __name__ == "__main__":
    sol = Solution()
    # expression = "{a,b}{c,{d,e}}"
    # expression = "{{a,z},a{b,c},{ab,z}}"
    expression = "{a,b}c{d,e}f"
    print(sol.braceExpansionII(expression))