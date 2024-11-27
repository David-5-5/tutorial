# 贪心专题 从最左/最右开始贪心
class Solution:
    def minMovesToMakePalindrome(self, s: str) -> int:
        # 自行解答
        ans = 0
        sl = list(s)

        while sl:
            # 查找和 sl[0] 匹配的字母的最后位置，得到移动的最短距离
            last = len(sl)-1 
            while sl[last] != sl[0]:
                last -= 1
            if last == 0: # last == 0, 表示仅单个字符，移动到字符串中间
                ans += len(sl) // 2
                sl = sl[1:]
            else: # 增加将last位置字符移动到末尾的次数，并移除首位字符
                ans += len(sl) - last - 1
                sl = sl[1:last] + sl[last+1:]
        
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    s = "letelt"
    print(sol.minMovesToMakePalindrome(s))