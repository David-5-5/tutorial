#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.5 排列型回溯
class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        // 按靠左的位置填可能的最大的值，而不是遍历最大的值，填可选择的位置
        int len = 2*n - 1;
        vector<int> ans(len);
        vector<bool> used(n+1);

        auto dfs = [&](this auto&& dfs, int idx) -> bool {
            while (idx < len && ans[idx] !=0 ) idx++;
            if (idx == len) return true;  // 填充结束

            for (int j=n; j; j--) {     // 最左的位置，从大填到小
                if (used[j]) continue;
                int sec = j>1? idx + j :idx;  // 注意下标
                
                if (sec < len && ans[idx] == 0 && ans[sec] == 0) {
                    ans[idx] = j; ans[sec] = j; used[j] = true;
                    if (dfs(idx+1)) return true;
                    ans[idx] = 0; ans[sec] = 0; used[j] = false;
                } 
            }
            return false;
        };

        dfs(0);
        return ans;
    }

};