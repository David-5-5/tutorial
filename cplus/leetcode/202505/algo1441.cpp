#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.1 基础
class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        // 自行解答
        vector<string> ans;

        int i = 1;
        for (auto& v : target) {
            while (i < v) {         // 不在 target 中的值，进栈出栈
                ans.push_back("Push");      
                ans.push_back("Pop");
                i ++;
            }
            ans.push_back("Push");  // 在 target 中的值，进栈
            i ++;
        }

        return ans;   
    }
};