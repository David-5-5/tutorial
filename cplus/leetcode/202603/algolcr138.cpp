#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    bool validNumber(string s) {
        // 自行解答
        // 将 s 的前后空格去掉后，建立状态机： 
        // 初始状态 0, 可接受如下字符
        //     1, +/-  ->  状态 1
        //     2, .    ->  状态 2
        //     3, 0~9  ->  状态 3
        // 带符号状态 1, 可接受如下字符
        //     1, .    ->  状态 2
        //     2, 0~9  ->  状态 3
        // 不完整小数状态 2, 可接受如下字符
        //     1, 0~9  ->  状态 4
        // 整数状态 3, 可接受如下字符
        //     1, 0~9  ->  状态 3
        //     2, .    ->  状态 4
        //     3. e/E  ->  状态 5
        // 小数状态 4, 可接受如下字符
        //     1, 0~9  ->  状态 4
        //     2, .    ->  状态 4
        //     3. e/E  ->  状态 5
        // 不完整科学计数状态 5, 可接受如下字符
        //     1, 0~9  ->  状态 6
        //     2. +,-  ->  状态 7
        // 不完整科学计数带符号状态 7, 可接受如下字符
        //     1, 0~9  ->  状态 6
        // 科学计数状态 6, 可接受如下字符
        //     1, 0~9  ->  状态 6
        
        // 状态 3, 4, 6 为可结束状态        
        // 去除前后空格
        size_t start = s.find_first_not_of(' ');
        if (start == string::npos) return false;
        size_t end = s.find_last_not_of(' ');
        s = s.substr(start, end - start + 1);
        
        int state = 0;
        for (char ch : s) {
            if (state == 0) {
                if (ch == '+' || ch == '-') state = 1;
                else if (ch == '.') state = 2;
                else if (ch >= '0' && ch <= '9') state = 3;
                else return false;
            } else if (state == 1) {
                if (ch == '.') state = 2;
                else if (ch >= '0' && ch <= '9') state = 3;
                else return false;
            } else if (state == 2) {
                if (ch >= '0' && ch <= '9') state = 4;
                else return false;
            } else if (state == 3) {
                if (ch == '.') state = 4;
                else if (ch >= '0' && ch <= '9') state = 3;
                else if (ch == 'e' || ch == 'E') state = 5;
                else return false;
            } else if (state == 4) {
                if (ch >= '0' && ch <= '9') state = 4;
                else if (ch == 'e' || ch == 'E') state = 5;
                else return false;
            } else if (state == 5) {
                if (ch >= '0' && ch <= '9') state = 6;
                else if (ch == '+' || ch == '-') state = 7;
                else return false;
            } else if (state == 6 || state == 7) {
                if (ch >= '0' && ch <= '9') state = 6;
                else return false;
            }
        }
        return state == 3 || state == 4 || state == 6;
    }
};