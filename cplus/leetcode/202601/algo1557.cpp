#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.1 拓扑排序
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        // 自行节点 toplogy sort
        vector<int> degree(n);
        for (auto& e: edges) degree[e[1]]++;
        vector<int> ans;
        for (int i=0; i<n; ++i) if (degree[i] == 0) ans.emplace_back(i);

        return ans;
    }
};