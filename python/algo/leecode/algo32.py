class Solution:
    # 同 codeforces 5C
    def longestValidParentheses(self, s: str) -> int:
        # 2022 自行解答，使用 stack，但代码比较混乱
        # 当时的思路应是stack留下来的 ”坏“括号数量为关键字，
        # 每段”坏“括号之间的括号数量即为最长的有效括号
        stack = []
        stackLen = 0
        countDict ={}
        cur = 0
        for brack in s:
            if len(stack)>0 and stack[len(stack)-1] == '(' and brack == ')':
                del(stack[-1])
                stackLen -= 1
                if cur > stackLen:
                    prev = countDict[cur]
                    countDict[cur] = 0
                    if stackLen in countDict:
                        countDict[stackLen] = countDict[stackLen] + prev + 2
                    else:
                        countDict[stackLen] = prev + 2
                else:
                    if stackLen in countDict:
                        countDict[stackLen] = countDict[stackLen] + 2
                    else:
                        countDict[stackLen] = 2
                cur = stackLen
            else:
                stack.append(brack)
                stackLen += 1
            # for key in countDict:
            #     longest = max(longest, countDict[key])
        return max(countDict.values())

    
    def longestValidParentheses2(self, s: str) -> int:
        # 参考题解，括号的动态规划 括号DP 模板 2024.10.16
        # - 对于 s[i] 为 '(' 其 dp[i] = 0
        # - 对于 s[i] 为 ')',
        #   - 若 s[i-1] 为 '(' 则 dp[i] = dp[i-2]+2
        #   - 若 s[i-1] 为 ')' 若 s[i-dp[i-1]-1]='(' 
        #     则 dp[i] = dp[i-1]+ dp[i-dp[i-1]-2] + 2
        dp = [0] * len(s)
        for i, ch in enumerate(s):
            if ch == ')':
                if i - 1 >= 0:
                    if s[i-1] == '(':
                        dp[i] = 2 + (dp[i-2] if i>1 else 0)
                    if s[i-1] == ')' and i-dp[i-1]-1 >= 0 and s[i-dp[i-1]-1]=='(' :
                        dp[i] = 2 + dp[i-1] + (dp[i-dp[i-1]-2]if i-dp[i-1]-1 > 0 else 0)
        return max(dp) if dp else 0

    def longestValidParentheses3(self, s: str) -> int:
        # 参考题解，简化 longestValidParentheses stack写法 2024.10.17
        # stack 保留的最后一个无法匹配的 ')' 数组索引。
        stack = []
        stack.append(-1)
        ans = 0
        for i, ch in enumerate(s):
            if ch == '(':
                stack.append(i)
            else: # ch == ')'
                if stack[-1]>=0 and s[stack[-1]] == '(':
                    stack.pop()
                    ans = max(ans, i - stack[-1])
                else:
                    stack.append(i)
        return ans

    def longestValidParentheses4(self, s: str) -> int:
        # left, right 2024.10.17, 需要正反遍历两次，取最大值
        ans = left = right =  0
        for ch in s:
            if ch == '(':
                left += 1
            else: # ch == ')'
                if left > right:
                    right += 1
                    if left == right and 2 * right > ans: ans = left + right
                else:
                    left = right = 0
        
        left = right =  0
        
        for ch in reversed(s):
            if ch == ')':
                right += 1
            else: # ch == ')'
                if right > left:
                    left += 1
                    if left == right and 2 * right > ans: ans = 2 * right
                else:
                    left = right = 0
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.longestValidParentheses(")()()("))
    # print(sol.longestValidParentheses2(")()()("))
    #print(sol.longestValidParentheses("()()"))
    print(sol.longestValidParentheses("((())())(()))(()()(()(()))(()((((()))))))((()())()))()()(()(((((()()()())))()())(()()))((((((())))((()))()()))))(()))())))()))()())((()()))))(()(((((())))))()((()(()(())((((())(())((()()(()())))())(()(())()()))())(()()()))()(((()())(((()()())))(((()()()))(()()))()))()))))))())()()((()(())(()))()((()()()((())))()(((()())(()))())())))(((()))))())))()(())))()())))())()((()))((()))()))(((())((()()()(()((()((())))((()()))())(()()(()))))())((())))(()))()))))))()(()))())(()())))))(()))((())(()((())(((((()()()(()()())))(()())()((()(()()))(()(())((()((()))))))))(()(())()())()(()(()(()))()()()(()()())))(())(()((((()()))())))(())((()(())())))))())()()))(((())))())((()(()))(()()))((())(())))))(()(()((()((()()))))))(()()()(()()()(()(())()))()))(((()(())()())(()))())))(((()))())(()((()))(()((()()()(())()(()())()(())(()(()((((())()))(((()()(((()())(()()()(())()())())(()(()()((()))))()(()))))(((())))()()))(()))((()))))()()))))((((()(())()()()((()))((()))())())(()((()()())))))))()))(((()))))))(()())))(((()))((()))())))(((()(((())))())(()))))(((()(((((((((((((())(((()))((((())())()))())((((())(((())))())(((()))))()())()(())())(()))))()))()()()))(((((())()()((()))())(()))()()(()()))(())(()()))()))))(((())))))((()()(()()()()((())((((())())))))((((((()((()((())())(()((()))(()())())())(()(())(())(()((())((())))(())())))(()()())((((()))))((()(())(()(()())))))))))((()())()()))((()(((()((()))(((((()()()()()(()(()((()(()))(()(()((()()))))()(()()((((((()((()())()))((())()()(((((()(()))))()()((()())((()())()(())((()))()()(()))"))
    print(sol.longestValidParentheses4("((())())(()))(()()(()(()))(()((((()))))))((()())()))()()(()(((((()()()())))()())(()()))((((((())))((()))()()))))(()))())))()))()())((()()))))(()(((((())))))()((()(()(())((((())(())((()()(()())))())(()(())()()))())(()()()))()(((()())(((()()())))(((()()()))(()()))()))()))))))())()()((()(())(()))()((()()()((())))()(((()())(()))())())))(((()))))())))()(())))()())))())()((()))((()))()))(((())((()()()(()((()((())))((()()))())(()()(()))))())((())))(()))()))))))()(()))())(()())))))(()))((())(()((())(((((()()()(()()())))(()())()((()(()()))(()(())((()((()))))))))(()(())()())()(()(()(()))()()()(()()())))(())(()((((()()))())))(())((()(())())))))())()()))(((())))())((()(()))(()()))((())(())))))(()(()((()((()()))))))(()()()(()()()(()(())()))()))(((()(())()())(()))())))(((()))())(()((()))(()((()()()(())()(()())()(())(()(()((((())()))(((()()(((()())(()()()(())()())())(()(()()((()))))()(()))))(((())))()()))(()))((()))))()()))))((((()(())()()()((()))((()))())())(()((()()())))))))()))(((()))))))(()())))(((()))((()))())))(((()(((())))())(()))))(((()(((((((((((((())(((()))((((())())()))())((((())(((())))())(((()))))()())()(())())(()))))()))()()()))(((((())()()((()))())(()))()()(()()))(())(()()))()))))(((())))))((()()(()()()()((())((((())())))))((((((()((()((())())(()((()))(()())())())(()(())(())(()((())((())))(())())))(()()())((((()))))((()(())(()(()())))))))))((()())()()))((()(((()((()))(((((()()()()()(()(()((()(()))(()(()((()()))))()(()()((((((()((()())()))((())()()(((((()(()))))()()((()())((()())()(())((()))()()(()))"))
    print(sol.longestValidParentheses4("(()"))
