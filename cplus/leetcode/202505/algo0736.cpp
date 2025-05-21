#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
private:
    unordered_map<string, vector<int>> scope;

public:
    int evaluate(string expression) {
        // 参考题解
        int start = 0;
        return innerEvaluate(expression, start);
    }


    int innerEvaluate(const string& exp, int& i) {
        if (exp[i] != '(') {            // 非表达式
            if (islower(exp[i])) {      // 变量
                string var = parseVar(exp, i);
                return scope[var].back();
            } else {                    // 整数
                return parseVal(exp, i);
            }
        }
        int ret;
        i ++;                // 跳过左括号
        if (exp[i] == 'l') { // let
            i += 4;          // 跳过 "let "
            vector<string> vars;
            while (true) {
                if (!islower(exp[i])) {
                    ret = innerEvaluate(exp, i);
                    break;
                }
                string var = parseVar(exp, i);
                if (exp[i] == ')') {
                    ret = scope[var].back();
                    break;
                }
                vars.push_back(var);
                i ++;           // 跳过 " "
                int e = innerEvaluate(exp, i);
                scope[var].push_back(e);
                i++;
            }
            for (auto var: vars) {
                scope[var].pop_back();
            }
        } else if (exp[i] == 'a') {  // add 表达式
            i += 4;                  // 跳过 "add "
            int e1 = innerEvaluate(exp, i);
            i ++;                    // 跳过 " "
            int e2 = innerEvaluate(exp, i);
            ret = e1 + e2;
        } else if (exp[i] == 'm') {  // add 表达式
            i += 5;                  // 跳过 "mult "
            int e1 = innerEvaluate(exp, i);
            i ++;                    // 跳过 " "
            int e2 = innerEvaluate(exp, i);
            ret = e1 * e2;
        }
        i++;                        // 移除右括号
        return ret;
    }

    string parseVar(const string& exp, int& i) {
        int n = exp.length();
        string ret;
        while (i<n && exp[i]!= ' ' && exp[i] != ')') {
            ret.push_back(exp[i++]);
        }
        return ret;
    }

    int parseVal(const string& exp, int& i) {
        int n = exp.length();
        int ret = 0, sign = 1;
        if (exp[i] == '-') {
            sign = -1, i++;
        }
        while (i < n && isdigit(exp[i])) {
            ret = ret * 10 + (exp[i++] - '0');

        }
        return sign * ret;
    }

};