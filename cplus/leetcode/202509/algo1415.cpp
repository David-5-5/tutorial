#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索
class Solution {
public:
    string getHappyString(int n, int k) {
        // 自行解答 按照题意进行回溯
        vector<string> ans;

        auto dfs = [&] (this auto&& dfs, string& str) -> void {
            if (ans.size() == k) return;
            if (str.length() == n) {
                ans.push_back(str);
                return;
            }
            for (int i=0; i<3; ++i) {
                if (str.size() && str.back() == 'a' + i) continue;
                str.push_back('a' + i);
                dfs(str);
                str.pop_back();
            }

        };
        string str = "";
        dfs(str); return ans.size()==k?ans.back():"";
    }
};