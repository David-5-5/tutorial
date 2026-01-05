#include <bits/stdc++.h>
using namespace std;

// 二、字符串 Z 函数（后缀的前缀）
class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        // 同 3292
        // z 函数 模板
        auto zFunc = [&](string& text) -> vector<int>{
            int t_len = (int)text.length();
            vector<int> ans(t_len);
            for (int i = 1, l = 0, r = 0; i < t_len; ++i) {
                if (i <= r && ans[i - l] < r - i + 1) {
                    ans[i] = ans[i - l];
                } else {
                    ans[i] = max(0, r - i + 1);
                    while (i + ans[i] < t_len && text[ans[i]] == text[i + ans[i]]) ++ans[i];
                }
                if (i + ans[i] - 1 > r) l = i, r = i + ans[i] - 1;
            }
            return ans;
        };
        // z函数 模板
        
        // 区间覆盖 
        auto merge = [] (vector<pair<int, int>> intervals, int n) -> int {
            sort(intervals.begin(), intervals.end());
            int min_cnt = 0, cur_pos = 0, max_reach = INT_MIN, i = 0, m = intervals.size();
            while (cur_pos <= n - 1) {
                while (i < m && intervals[i].first <= cur_pos) max_reach = max(max_reach, intervals[i++].second);
                if (max_reach < cur_pos) return -1;
                min_cnt++;
                cur_pos = max_reach + 1;
                if (max_reach >= n - 1) break;
            }
            return max_reach >= n - 1 ? min_cnt : -1;
        };

        vector<pair<int, int>> intervals;
        
        for (auto& word : words) {
            string text = word + target; int m = word.size(), n = text.size(); 
            auto zres = zFunc(text);
            int i = m;
            for (int i=m; i<n; ++i) if (zres[i]) 
                intervals.emplace_back(i-m, i-m+min(m, zres[i])-1);
        }

        return merge(intervals, target.size());         
    }
};