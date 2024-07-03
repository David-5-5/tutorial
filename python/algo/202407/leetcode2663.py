# 贪婪算法，把字符当作 k 进制数字处理，
# 1, 从最后一个字符开始，执行加 1, 若加一等于 a，则进位，
#    上一位也需要增加 1. (注由于起始为美丽字符，因此最多一位进位一次，不可能连续两位进位)
# 2, 执行循环 当前索引(从零开始)小于字符长度
#    2.1 比较加一后的字符与前两位字符是否相等，若想等则是不是美丽字符，转到步骤 1 ，指定位执行加一操作
#    2.2 若不相等，不构成回文串，当前位置加一，转到步骤 2
# 3, 返回结果
class Solution:
    def smallestBeautifulString(self, s: str, k: int) -> str:
        sl = list(s)
        oa = ord('a')
        
        def add(inx:int) -> int:
            sl[inx] = chr((ord(sl[inx]) + 1 - oa) % k + oa)
            if sl[inx] == 'a':
                return add(inx-1)   
            return inx

        inx = add(len(sl) - 1)
        while inx < len(sl):
            if (inx > 0 and sl[inx-1] == sl[inx]) or (inx > 1 and sl[inx-2] == sl[inx]):
                inx = add(inx)
            else:
                inx += 1
        ns = ''.join(sl)
        return ns if ns > s else ""

if __name__ == "__main__":
    sol = Solution()
    print(sol.smallestBeautifulString("dacd", 4))
                

        
