class Solution:
    def strWithout3a3b(self, a: int, b: int) -> str:
        # 自行解答，构造
        s = ''
        while a or b:
            if a > b:
               s += 'a' * min(2, a)
               a -= min(2, a)
               s += 'b' * min(1, b)
               b -= min(1, b)
            elif b > a:
               s += 'b' * min(2, b)
               b -= min(2, b)
               s += 'a' * min(1, a)
               a -= min(1, a)
            else:
                if len(s) and s[-1] == 'a':
                    s += 'ba' * a
                else: 
                    s += 'ab' * a
                break

        return s 