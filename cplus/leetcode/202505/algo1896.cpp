#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    int minOperationsToFlip(string expression) {
        // 参考题解，还不是很理解 动态规划
        // 
        // 数字栈，二元组 (x,y)，其中：
        //  x 表示将对应表达式的值变为 0，需要的最少操作次数，
        //  y 表示将对应表达式的值变为 1，需要的最少操作次数
        vector<pair<int, int>> stack_num;

        // 符号栈
        vector<char> stack_op;

        auto op_and = [] (int x1, int y1, int x2, int y2) -> pair<int, int> {
            return {min({x1+x2, x1+y2, y1+x2}), y1+y2};
        };
        auto op_or = [] (int x1, int y1, int x2, int y2) -> pair<int, int> {
            return {x1+x2, min({x1+y2, y1+x2, y1+y2})};
        };
        
        auto calc = [&]() {
            if (stack_num.size() >= 2 && (stack_op.back() == '|' || stack_op.back() == '&')) {
                auto [x1, y1] = stack_num.back();
                stack_num.pop_back();
                auto [x2, y2] = stack_num.back();
                stack_num.pop_back();

                auto [x_and, y_and] = op_and(x1, y1, x2, y2);
                auto [x_or, y_or] = op_or(x1, y1, x2, y2);
                if (stack_op.back() == '&') {
                    stack_num.emplace_back(min(x_and, x_or+1), min(y_and, y_or+1));
                } else {
                    stack_num.emplace_back(min(x_or, x_and+1), min(y_or, y_and+1));
                }
                stack_op.pop_back();
            }
        };

        for (auto & ch: expression) {
            if (ch == '(' || ch == '|' || ch == '&') {
                stack_op.push_back(ch);
            } else if (ch == '0') {
                stack_num.emplace_back(0, 1);
                calc();
            } else if (ch == '1') {
                stack_num.emplace_back(1, 0);
                calc();
            } else {
                assert(ch == ')');
                stack_op.pop_back();
                calc();
            }
        }
        return max(stack_num[0].first, stack_num[0].second);
    }
};