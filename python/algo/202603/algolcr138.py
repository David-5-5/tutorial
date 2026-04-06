class Solution:
    def validNumber(self, s: str) -> bool:
        '''
        将 s 的前后空格去掉后，建立状态机： 
        初始状态 0, 可接受如下字符
            1, +/-  ->  状态 1
            2, .    ->  状态 2
            3, 0~9  ->  状态 3
        带符号状态 1, 可接受如下字符
            1, .    ->  状态 2
            2, 0~9  ->  状态 3
        不完整小数状态 2, 可接受如下字符
            1, 0~9  ->  状态 4
        整数状态 3, 可接受如下字符
            1, 0~9  ->  状态 3
            2, .    ->  状态 4
            3. e/E  ->  状态 5
        小数状态 4, 可接受如下字符
            1, 0~9  ->  状态 4
            2, .    ->  状态 4
            3. e/E  ->  状态 5
        不完整科学计数状态 5, 可接受如下字符
            1, 0~9  ->  状态 6
            2. +,-  ->  状态 7
        不完整科学计数带符号状态 7, 可接受如下字符
            1, 0~9  ->  状态 6
        科学计数状态 6, 可接受如下字符
            1, 0~9  ->  状态 6
        
        状态 3, 4, 6 为可结束状态
        '''
        s = s.strip()
        state = 0
        for ch in s:
            if state == 0:
                if ch in ['+', '-']: state = 1
                elif ch == '.': state = 2
                elif '0' <= ch <= '9': state = 3
                else: return False
            elif state == 1:
                if ch == '.': state = 2
                elif '0' <= ch <= '9': state = 3
                else: return False
            elif state == 2:
                if '0' <= ch <= '9': state = 4
                else: return False
            elif state == 3:
                if ch == '.': state = 4
                elif '0' <= ch <= '9': state = 3
                elif ch in ['e', 'E']: state = 5
                else: return False
            elif state == 4:
                if '0' <= ch <= '9': state = 4
                elif ch in ['e', 'E']: state = 5
                else: return False
            elif state == 5:
                if '0' <= ch <= '9': state = 6
                elif ch in ['+', '-']: state = 7
                else: return False
            elif state == 6 or state == 7:
                if '0' <= ch <= '9': state = 6
                else: return False

        return state in [3, 4, 6]