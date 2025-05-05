#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  2.1 一维差分
class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        // 自行解答
        map<int, long long> color;

        for (auto& seg : segments) {
            int l = seg[0], r = seg[1], c = seg[2];
            color.count(l)? color[l]+=c: color[l]=c;
            color.count(r)? color[r]-=c: color[r]=-c;
        }
        
        vector<vector<long long>> ans;
        long prev = 0, col = 0, start = 0;
        for (auto& [i, c]: color) {
            if (start && col) ans.push_back({start, i, col});
            start = i;
            col += c;
        }

        return ans;    
    }

    vector<vector<long long>> splitPainting2(vector<vector<int>>& segments) {
        // 使用 unordered_map + vector + sort 性能优于 map
        unordered_map<int, long long> color;

        for (auto& seg : segments) {
            int l = seg[0], r = seg[1], c = seg[2];
            color.count(l)? color[l]+=c: color[l]=c;
            color.count(r)? color[r]-=c: color[r]=-c;
        }
        
        vector<pair<int, long long>> v_col;
        for (auto& [i, c]: color) v_col.push_back({i, c});
        sort(v_col.begin(), v_col.end());

        vector<vector<long long>> ans;
        long prev = 0, col = 0, start = 0;
        for (auto& [i, c]: v_col) {
            if (start && col) ans.push_back({start, i, col});
            start = i;
            col += c;
        }

        return ans;    
    }
};