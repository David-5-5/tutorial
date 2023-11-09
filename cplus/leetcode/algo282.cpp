#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> addOperators(std::string num, int target) {
        int n = num.size();
        std::vector<std::string> ans;
        
        std::vector<std::tuple<int, std::string, int, int>> ops;
        ops.push_back(std::make_tuple(0, "", 0, 0));
        int count = 0;
        while (!ops.empty()) {
            count++;
            int inx, ret, mul;
            std::string expr;
            std::tie(inx, expr, ret, mul) = ops.front();
            ops.erase(ops.begin());
            if (inx == n) {
                if (ret == target) {
                    ans.push_back(expr);
                }
                continue;
            }
            for (int i = 1; i <= n - inx; i++) {
                if (num[inx] == '0' && i > 1) {
                    break;
                }
                int val = std::stoi(num.substr(inx, i));
                if (inx == 0) {
                    ops.push_back(std::make_tuple(i, num.substr(inx, i), val, val));
                } else {
                    ops.push_back(std::make_tuple(i + inx, expr + "*" + num.substr(inx, i), ret - mul + mul * val, mul * val));
                    ops.push_back(std::make_tuple(i + inx, expr + "+" + num.substr(inx, i), ret + val, val));
                    ops.push_back(std::make_tuple(i + inx, expr + "-" + num.substr(inx, i), ret - val, -val));
                }
            }
        }
        std::cout << count << std::endl;
        return ans;
    }
};

int main() {
    Solution solution;
    std::vector<std::string> result = solution.addOperators("123", 6);
    for (const std::string& expr : result) {
        std::cout << expr << std::endl;
    }
    return 0;
}