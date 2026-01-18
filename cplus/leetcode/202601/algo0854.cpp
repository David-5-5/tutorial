#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.3 图论建模 + BFS 最短路
class Solution {
public:
    int kSimilarity(string s1, string s2) {
        // 自行解答，暴力 BFS 超时
        set<string> vis; vector<pair<string, int>> q; int n = s1.length();
        vis.insert(s1); q.emplace_back(s1, 0); int k = 0;

        long long loop = 0;
        while (!q.empty()) {        // 元素当前字符串，交换位置，逐一完成字符的交换
            vector<pair<string, int>> nxt;
            for (auto & [u, p]: q) {
                if (u == s2) {
                    return k;
                }
                while (p<n && u[p] == s2[p]) p++;
                for (int j=p+1; j<n; ++j) {
                    if (u[j] == s2[j] || u[j] != s2[p] ) continue;      // 剪枝
                    auto v = u; swap(v[p], v[j]);
                    if (vis.insert(v).second) nxt.emplace_back(v, p+1);
                }
            }
            q = move(nxt); k ++;
        }
        
        return -1;   
    }

};