#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.2 广度优先搜索（BFS）
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        // 自行解答
        int n = watchedVideos.size(); vector<bool> vis(n);

        vector<int> q = {id}; int step = 0; vis[id] = true;
        while (step++ < level) {
            vector<int> nxt;
            for (auto& u: q) {
                for (auto& v: friends[u]) {
                    if (vis[v]) continue;
                    vis[v] = true;
                    nxt.push_back(v);
                }
            }
            q = move(nxt);
        }

        unordered_map<string, int> freqs; 
        for (auto& u: q) for (auto& v: watchedVideos[u]) freqs[v] ++;

        vector<string> ans; for (auto& [v, _]: freqs) ans.push_back(v);
        sort(ans.begin(), ans.end(), [&](const string& a, const string& b){
            if (freqs[a] == freqs[b]) return a < b;
            return freqs[a] < freqs[b];
        });
        return ans;
    }
};