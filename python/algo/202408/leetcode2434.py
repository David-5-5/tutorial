# 周赛 314
class Solution:
    def robotWithString(self, s: str) -> str:
        # 自行解答
        n = len(s)
        
        # 定义 mins 数组，表示 i及以后最小的字符
        mins = [''] * (n+1)
        mins[n] = 'z' # 哨兵
        for i in range(n-1,-1,-1):
            mins[i] = min(mins[i+1], s[i])

        st, toprint = [], [] 
        for i, ch in enumerate(s):
            while st and st[-1] <= mins[i]:  # 栈顶元素小于等于后续所有字符出栈并打印
                toprint.append(st.pop()) 
            st.append(ch) # 当前元素大于后续某个元素，进栈
        
        while st: # 后进先出打印字符
            toprint.append(st.pop())
        return "".join(toprint)

if __name__ == "__main__":
    sol = Solution()
    print(sol.robotWithString("bdda"))