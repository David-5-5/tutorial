#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 2.1 
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        // 自行解答 连通块 不相交集
        vector<pair<int, int>> distinct(26, {-1, -1}); int n = s.length();

        for (int i=0; i<n; ++i) {
            auto ch = s[i] - 'a';
            if (distinct[ch].first == -1) distinct[ch].first = i;
            distinct[ch].second = i;
        }
        vector<vector<int>> g(26, vector<int>(26, 0));
        for (int i=0; i<26; i++) {
            if (distinct[i].first == -1) continue;
            for (int j=distinct[i].first+1; j<distinct[i].second; j++) if (s[j]-'a' != i) g[i][s[j]-'a'] = 1;
        }

        for (int i=0; i<26; i++) {
            if (distinct[i].first == -1) continue;
            vector<bool> vis(26); vector<int> cc;   // connected component

            auto dfs = [&](this auto&& dfs, int u) -> void {
                vis[u] = true; cc.emplace_back(u);
                for (int v=0; v<26; v++) {
                    if (v == u || vis[v] || g[u][v] == 0) continue;
                    dfs(v);
                }
            };
            
            dfs(i);
            for (auto u: cc) {
                distinct[i].first = min(distinct[u].first, distinct[i].first);
                distinct[i].second = max(distinct[u].second, distinct[i].second);
            }
        }

        sort(distinct.begin(), distinct.end(), [](const pair<int,int> a, const pair<int, int> b) {
            return a.second < b.second; // sort by right
        });
        distinct.erase(unique(distinct.begin(), distinct.end()), distinct.end());

        int cnt = 0, right = -1;
        for (auto &[l, r] : distinct) {
            if (l == -1 || l <= right) continue;
            if (l == 0  && r == n-1) continue;
            right = r; cnt ++;
        }
        return cnt >= k;   
    }
};

int main() {
    cout << Solution().maxSubstringLength("ddjlopbgngpoenkqktvuuvpygctyquoeqglszijjiifljfiswiladdfwzislzdd", 6);
}