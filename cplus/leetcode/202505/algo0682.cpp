#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.1 基础
class Solution {
public:
    int calPoints(vector<string>& operations) {
        // 自行解答
        vector<int> scores;
        int ans = 0;

        for (auto& op : operations) {
            int val = 0;
            if (op == "+") {
                val = scores[scores.size()-1] + scores[scores.size()-2];
                scores.push_back(val);
            } else if (op == "D") {
                val = 2 * scores[scores.size()-1];
                scores.push_back(val);
            } else if (op == "C") {
                val -= scores[scores.size()-1];
                scores.pop_back();
            } else {
                scores.push_back(stoi(op));
                val = scores[scores.size()-1];
            }
            ans += val;
        }

        return ans;

    }
};