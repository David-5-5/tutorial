class Solution:
    def lastSubstring(self, s: str) -> str:
        ret = []
        for let in s:
            # 找出字典序最大字母开头的子串
            if not ret:
                ret.append(let)
            else:
                if ret[0] < let:
                    ret = [let]
                else:
                    ret.append(let)
        candidate = ''.join(ret)
        
        result = candidate
        for i in range(0, len(candidate)-1):
            if candidate[i] < candidate[0] and candidate[i+1] == candidate[0]:
                # 候选字串中，相同最大字典序字母在中间出现后的子串，要去前一个字符的字典序小于最大序字母
                # 类如y为最大字典序字母，yuyx，yuyx子串比较yx子串的大小
                # 若子串为yyyx，yyy开头的子串一定是最大字典序的，则无候选子串可供比较
                result = max(result, candidate[i+1:])

        return result
        

if __name__ == "__main__":
    sol = Solution()
    s = "abab"
    print(sol.lastSubstring(s))