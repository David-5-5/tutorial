#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    int calculate(string s) {
        // 复习 参考题解 自行解答参见 python
        stack<int> ops; 
        // 删除空格       
        s.erase(remove(s.begin(), s.end(), ' '), s.end());

        int sign = 1, ret = 0, n = s.length(), i = 0;
        ops.push(sign);                // 当前操作数的正负，默认正
        
        while (i < n) {
            if (s[i] == '+') {
                sign = ops.top();
                i++;
            } else if (s[i] == '-') {
                sign = -ops.top();
                i++;
            } else if (s[i] == '(') {
                ops.push(sign);
                i++;
            } else if (s[i] == ')') {
                ops.pop();
                i++;
            }else {
                long num = 0;
                while (i<n && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
};