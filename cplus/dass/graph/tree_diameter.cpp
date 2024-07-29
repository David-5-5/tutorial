#include <bits/stdc++.h>
using namespace std;

// 树上任意两节点之间最长的简单路径即为树的「直径」。

// Using two dfs
// 首先从任意节点 y 开始进行第一次 DFS，到达距离其最远的节点，记为 z，
// 然后再从 z 开始做第二次 DFS，到达距离 z 最远的节点，记为 z'，
// 则 \delta(z,z') 即为树的直径。
// 
void diameter(int n, vector<int>* g, int begin) {
    int c=0, d[n];

    function<void(int, int)> dfs = [&](int u, int fa){
        for (int v : g[u]) {
            if (v == fa) continue;
            d[v] = d[u] + 1;
            if (d[v] > d[c]) c = v;
            dfs(v, u);
        }
    };

    dfs(begin, -1);
    cout << "End1: " << c;
    d[c] = 0, dfs(c, -1);
    cout << " End2: " << c << " Diameter: " << d[c] << endl;
}


// Using dp
void diameterInDp(int n, vector<int>* g) {
    
    // 最长路径d1, 次长路径 d2, d1与d2无公共边
    int d = 0, d1[n], d2[n];

    function<void(int, int)> dfs = [&](int u, int fa){
        d1[u] = d2[u] = 0;
        for (int v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
            int t = d1[v] + 1;
            if (t > d1[u])
                d2[u] = d1[u], d1[u] = t;
            else if (t > d2[u])
                d2[u] = t;
        }
        d = max(d, d1[u] + d2[u]);
    };
    dfs(9, -1);
    cout << " Diameter: " << d << endl;
}

// Using dp
void diameterInDp2(int n, vector<int>* g) {
    
    // 最长路径d1, 次长路径 d2, d1与d2无公共边
    int d = 0, dp[n];

    function<void(int, int)> dfs = [&](int u, int fa){
        dp[u] = 0;
        for (int v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
            d = max(d, dp[u] + dp[v] + 1);
            dp[u] = max(dp[u], dp[v] + 1);
        }
        
    };
    dfs(4, -1);
    cout << " Diameter: " << d << endl;
}


int main() {
    vector<pair<int, int>> edges = {{3,0},{7,0},{1,2},{1,3},{2,4},{2,5},{3,6},{5,8},{8,9}};
    int n = 10;
    vector<int> g[n];
    for (int i = 0; i < edges.size(); i++) {
        g[edges[i].first].push_back(edges[i].second);
        g[edges[i].second].push_back(edges[i].first);
    }

    // diameter(n, g, 1);
    // diameterInDp(n,g);
    diameterInDp2(n,g);
}