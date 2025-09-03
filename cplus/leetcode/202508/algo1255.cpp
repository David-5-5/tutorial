#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        // 自行解答，遍历，性能较差 240s
        int n = words.size();
        vector<unordered_map<char, int>> w_cnt(n); unordered_map<char, int> l_cnt;
        for (auto& ch: letters) l_cnt[ch-'a'] ++;
        for (int i=0; i<n; ++i) for (auto&ch:words[i]) w_cnt[i][ch-'a']++;

        int mx_score = 0;
        for (int mask=0; mask<(1<<n); ++mask) {
            int cur_score = 0; unordered_map<char, int> left_cnt; 
            for (auto [k, v]:l_cnt) left_cnt[k]=v;

            for (int i=0; i<n; ++i) if ((mask >> i) & 1){
                bool contain = true;
                for (auto& [k, v]: w_cnt[i]) if (!left_cnt.count(k)||left_cnt[k]<v) {
                    contain = false; break;
                }
                if (contain) {
                    for (auto& [k, v]: w_cnt[i]) {
                        left_cnt[k] -= v;
                        cur_score += score[k] * v;
                        if (left_cnt[k] == 0) left_cnt.erase(k);
                    }
                }
                if (left_cnt.size() == 0) break;
            }
            mx_score = max(mx_score, cur_score);
        }

        return mx_score; 
    }

    int maxScoreWords2(vector<string>& words, vector<char>& letters, vector<int>& score) {
        // 自行解答，递归，性能不错 4s
        int n = words.size();
        vector<unordered_map<char, int>> w_cnt(n); unordered_map<char, int> l_cnt;
        for (auto& ch: letters) l_cnt[ch-'a'] ++;
        for (int i=0; i<n; ++i) for (auto&ch:words[i]) w_cnt[i][ch-'a']++;

        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == n) return 0;
            
            int res = dfs(i+1); // 不选
            bool contains = true;
            for (auto&[k, v]:w_cnt[i]) if (!l_cnt.count(k) || l_cnt[k] < v) {
                contains = false; break;
            }

            if (contains) {
                int scr = 0;
                for (auto&[k, v]:w_cnt[i]) {l_cnt[k] -= v; scr += v * score[k];}
                res = max(res, dfs(i+1) + scr);
                for (auto&[k, v]:w_cnt[i]) l_cnt[k] += v;    // 恢复现场
            }
            return res;
        };
        return dfs(0);

    }


};