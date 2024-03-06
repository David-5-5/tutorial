#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct element {
    int inx;
    string expr;
    long res;
    long mul;
};

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        int n = num.length();
        vector<string> ans;
        
        vector<element> ops;

        ops.push_back(element{0, "", 0, 0});
        while (!ops.empty()) {
            // change the ops put/pop from queue to stack
            // element cur = ops.front();
            // ops.erase(ops.begin());
            element cur = ops.back();
            ops.erase(ops.end());
            if (cur.inx == n) {
                if (cur.res == target) {
                    ans.push_back(cur.expr);
                }
                continue;
            }
            for (int i = 1; i <= n - cur.inx; i++) {
                if (num[cur.inx] == '0' && i > 1) {
                    break;
                }
                long val = stol(num.substr(cur.inx, i));
                if (cur.inx == 0) {
                    ops.push_back(element{i, num.substr(cur.inx, i), val, val});
                } else {
                    ops.push_back(element{i + cur.inx, cur.expr + "*" + num.substr(cur.inx, i), cur.res - cur.mul + cur.mul * val, cur.mul * val});
                    ops.push_back(element{i + cur.inx, cur.expr + "+" + num.substr(cur.inx, i), cur.res + val, val});
                    ops.push_back(element{i + cur.inx, cur.expr + "-" + num.substr(cur.inx, i), cur.res - val, -val});
                }
            }
        }
        return ans;
    }

    vector<string> addOperators_recursion(string num, int target) {
        int n = num.length();
        vector<string> ans;
        
        function<void(string, int, long, long)> backtrack = [&](string expr, int inx, long res, long mul) {
            if (inx == n) {
                if (res == target) {
                    ans.push_back(expr);
                }
                return;
            }
            for (int i = 1; i <= n - inx; i++) {
                if (num[inx] == '0' && i > 1) {
                    break;
                }
                long val = stol(num.substr(inx, i));
                if (inx == 0) {
                    backtrack(num.substr(inx, i), i, val, val);
                } else {
                    backtrack(expr + "*" + num.substr(inx, i), i + inx, res - mul + mul * val, mul * val);
                    backtrack(expr + "+" + num.substr(inx, i), i + inx, res + val, val);
                    backtrack(expr + "-" + num.substr(inx, i), i + inx, res - val, -val);
                }
            }
        };
        string expr;
        backtrack(expr, 0, 0, 0);
        return ans;
    }

    /// expr transfer string to string&
    vector<string> addOperators3(string num, int target) {
        int n = num.length();
        vector<string> ans;
        
        function<void(string&, int, long, long)> backtrack = [&](string& expr, int inx, long res, long mul) {
            if (inx == n) {
                if (res == target) {
                    ans.push_back(expr);
                }
                return;
            }
            int signIndex = expr.size();
            if (inx > 0) {
                expr.push_back(0);
            }
            for (int i = 1; i <= n - inx; i++) {
                if (num[inx] == '0' && i > 1) {
                    break;
                }
                long val = stol(num.substr(inx, i));
                expr.push_back(num[inx+i-1]);
                if (inx == 0) {
                    backtrack(expr, i, val, val);
                } else {
                    expr[signIndex] = '*'; backtrack(expr, i + inx, res - mul + mul * val, mul * val);
                    expr[signIndex] = '+'; backtrack(expr, i + inx, res + val, val);
                    expr[signIndex] = '-'; backtrack(expr, i + inx, res - val, -val);
                }
            }
            expr.resize(signIndex);
        };
        string expr;
        backtrack(expr, 0, 0, 0);
        return ans;
    }
};



int main() {
    Solution solution;
    vector<string> result = solution.addOperators("123456789", 45);
    for (const string& expr : result) {
        cout << expr << endl;
    }
    return 0;
}