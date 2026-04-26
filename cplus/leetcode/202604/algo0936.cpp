#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.4 逆向思维
class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        // 参考题解，暴力, 类似toplogy sort
        vector<int> ans; int n = stamp.length(), m = target.length();
        vector<pair<set<int>, set<int>>> wins(m-n+1);
        vector<bool> seen(m);
        deque<int> q;   int cnt = 0;
        for (int i=0; i<=m-n; i++) {
            for (int j=0; j<n; j++) {
                if (stamp[j] == target[i+j]) wins[i].first.insert(i+j);
                else wins[i].second.insert(i+j);
            }
            
            if (wins[i].second.empty()) {
                ans.push_back(i);
                for (auto v: wins[i].first) if (!seen[v]) {
                    q.push_back(v); seen[v] = true;
                }
            }
        }
        
        while (!q.empty()) {
            auto inx = q.front(); q.pop_front();
            for (int i = max(0, inx-n+1); i<min(m-n+1, inx+n); i++) {
                // cout << i << endl;
                if (wins[i].second.contains(inx)) {
                    wins[i].second.erase(inx);
                    if (wins[i].second.empty()) {
                        ans.push_back(i);
                        for (auto v: wins[i].first) if (!seen[v]) {
                            q.push_back(v); seen[v] = true;
                        }
                    }
                }
            }
        }

        for (auto s: seen) if (!s) return {};
        reverse(ans.begin(), ans.end());
        return ans;  
    }    
};


int main() {
    Solution().movesToStamp("babe", "babeabeabebabbbabeee");
}