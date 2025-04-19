#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        vector<vector<int>> pres(5, vector<int>(n+1));

        for(int i=0; i<n; ++i) {
            int v = s[i] - '0';
            for (int j=0; j<5; ++j) {
                if (j==v) pres[j][i+1] = pres[j][i] + 1;
                else pres[j][i+1] = pres[j][i];
            }
        }

        int ans = INT_MIN;
        for (int a=0; a<5; ++a) for (int b=0; b<5; ++b) {
            if (a == b || pres[a][n] == 0 || pres[b][n] == 0) continue;

            vector<deque<pair<int,int>>> queue(4, deque<pair<int,int>>());
            // for (int i=0; i<4; ++i) queue[i].emplace_back(0, 0);
            for (int i=1; i<=n; i++) {

                int val = pres[a][i] - pres[b][i];

                if (pres[a][i]%2==1 && pres[b][i] && pres[b][i]%2==0 && i>=k) ans = max(ans, val);

                int cur = ((pres[a][i]%2) << 1) + (pres[b][i] % 2);
                int prev = ((1 ^ pres[a][i]%2 )<< 1) + (pres[b][i] % 2);

                while (queue[prev].size()>1 && i-queue[prev][1].first>=k) {
                    queue[prev].pop_front();
                }
                
                if (queue[prev].size() && i-queue[prev].front().first>=k
                        && (pres[b][i]-pres[b][queue[prev].front().first]))
                    ans = max(ans, val - queue[prev].front().second);
                
                if (queue[cur].size()==0 || queue[cur].back().second > val)
                    queue[cur].emplace_back(i, val);

            }
    
        }
        return ans;       
    }
};

int main() {
    cout << Solution().maxDifference("44114402", 7) << endl;
}