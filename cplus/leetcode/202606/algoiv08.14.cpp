#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countEval(string s, int result) {
        
        unordered_map<string, int> memo[2];

        auto dfs = [&](this auto&& dfs, string expr, int target) -> int{
            int n = expr.length();

            if (n == 1) return stoi(expr) == target;

            if (memo[target].count(expr)) return memo[target][expr];

            int res = 0;
            for (int i=1; i<n; i+=2) {
                auto left_0 = dfs(expr.substr(0, i), 0), left_1 = dfs(expr.substr(0, i), 1);
                auto right_0 = dfs(expr.substr(i+1), 0), right_1 = dfs(expr.substr(i+1), 1);

                if (expr[i] == '^') {
                    if (target)
                        res += left_0 * right_1 + left_1 * right_0;
                    else res += left_0 * right_0 + left_1 * right_1;
                } else if (expr[i] == '&') {
                    if (target) 
                        res += left_1 * right_1;
                    else res += left_0 * right_0 + left_0 * right_1 + left_1 * right_0;
                } else 
                    if (target) res += left_0 * right_1 + left_1 * right_0 + left_1 * right_1 ;
                    else res += left_0 * right_0;
            }

            return memo[target][expr] = res;
        };
        return dfs(s, result);
    }


};