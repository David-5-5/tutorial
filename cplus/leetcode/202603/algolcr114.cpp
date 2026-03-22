#include <bits/stdc++.h>
using namespace std;

// 同 269 会员题
class Solution {
public:
    string alienOrder(vector<string>& words) {
        // 自行解答
        vector<int> degree(26, -1); vector<vector<int>> g(26);
        int n = words.size();
        for (auto& w: words) for(int i=0; i<w.length(); ++i) 
            if(degree[w[i]-'a'] == -1) degree[w[i]-'a'] = 0;

        for (int i=1; i<n; i++) {
            auto s = words[i-1], t = words[i];
            // 特殊判断
            if (s.length()>t.length() && s.substr(0, t.length()) == t) return "";

            for (int i=0; i<min(s.length(), t.length()); i++) {
                if(s[i] != t[i]) {
                    g[s[i]-'a'].emplace_back(t[i]-'a');
                    degree[t[i]-'a'] ++;
                    break;
                }
            }
        }
        string ans = "";
        deque<int> q;
        for (int i=0; i<26; i++) if (degree[i] == 0) {
            q.push_back(i);
        }

        while (!q.empty()) {
            auto u  = q.front(); q.pop_front();
            ans.push_back(u + 'a');
            for (auto v: g[u]) {
                degree[v] --; if (degree[v] == 0) q.push_back(v);
            }
        }

        // 保证所有出现的字母都能排序输出，否则返回 ""
        for (int i=0; i<26; i++) if (degree[i] > 0) return "";
        
        return ans;
    }
};