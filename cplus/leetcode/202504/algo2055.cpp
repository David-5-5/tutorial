#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.1 前缀和基础
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        // 自行解答 使用 ranges::lower_bound ranges::upper_bound
        int n = s.length();
        vector<int> pres(n+1);
        vector<int> pos;
        for (int i=0; i<n; i++) {
            pres[i+1] = pres[i] + (s[i] == '*' ? 1 : 0);
            if (s[i] == '|') pos.push_back(i);
        }

        if (pos.size() == 0) return vector<int>(queries.size(), 0);

        vector<int> ans;
        for (auto & q : queries) {
            int l = ranges::lower_bound(pos, q[0]) - pos.begin();
            int r = ranges::upper_bound(pos, q[1]) - pos.begin();
            if (r == pos.size() || pos[r]>q[1]) r--;
            if (l < r) ans.push_back(pres[pos[r]]-pres[pos[l]]);
            else ans.push_back(0);
        }
        return ans;   
    }

    
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        // 自行解答 使用 set
        // 学习 set lower_bound upper_bound usage
        int n = s.length();
        vector<int> pres(n+1);
        set<int> pos;
        for (int i=0; i<n; i++) {
            pres[i+1] = pres[i] + (s[i] == '*' ? 1 : 0);
            if (s[i] == '|') pos.insert(i);
        }

        if (pos.size() == 0) return vector<int>(queries.size(), 0);

        vector<int> ans;
        for (auto & q : queries) {
            auto l = pos.lower_bound(q[0]);
            auto r = pos.upper_bound(q[1]);
            // r 是指针 r++ , r-- 在元素之间!!循环!!左移或右移，
            if (r == pos.end() || (r!=pos.begin() && *r>q[1])) r--;
            if (*l < *r) ans.push_back(pres[*r]-pres[*l]);
            else ans.push_back(0);
        }
        return ans;     
    }
};