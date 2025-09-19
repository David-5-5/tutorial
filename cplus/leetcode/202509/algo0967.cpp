#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索
class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> ans;

        if (n==1) {
            for (int i=0; i<10; ++i) ans.push_back(i);
            return ans;
        }

        auto dfs = [&] (this auto&& dfs, int val) -> void {
            if (to_string(val).length() == n) {
                ans.push_back(val);
                return;
            }
            int tail = val % 10;
            if (k == 0) dfs(val*10 + tail);
            else {
                if (tail-k >=0  && tail - k <=9) dfs(val*10 + tail-k);
                if (tail+k >=0  && tail + k <=9) dfs(val*10 + tail+k);
            }
        };

        for (int i=1; i<10; ++i) dfs(i);
        return ans;
    }
};