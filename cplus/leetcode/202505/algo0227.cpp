#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    int calculate(string s) {
        int begin = 0;
        vector<int> operand;
        vector<char> operation;
        const set<char> ops={'*', '/', '+', '-'};
        
        auto compare = [&](char op) -> bool {
            if (operation.size() == 0) return false;
            else if ((operation.back() == '-' || operation.back() == '+') &&
                (op == '*' || op == '/')) return false;

            return true;
        };

        auto cal = [&]() {
            int op1 = operand.back();
            operand.pop_back();
            if (operation.back() == '+') operand.back() += op1;
            else if (operation.back() == '-') operand.back() -= op1;
            else if (operation.back() == '*') operand.back() *= op1;
            else operand.back() /= op1;

            operation.pop_back();
        };

        for (int i = 0; i<s.length(); ++i) {
            if (ops.count(s[i])) {
                operand.push_back(stoi(s.substr(begin, i-begin)));
                if (compare(s[i])) {
                    cal();
                }
                operation.push_back(s[i]);
                begin = i + 1;
            }
        }
        operand.push_back(stoi(s.substr(begin, s.length()-begin)));
        while (operation.size()) {
            cal();
        }

        return operand[0];   
    }
};
