#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.1 并查集 - 基础
class UnionFind {                   // 并查集模板
    vector<int> fa;
public:
    UnionFind(int n): fa(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y;
        }
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // 自行解答
        int idx = 0;
        unordered_map<string, int> idx_email;       // 为每个邮箱生成 id，用于后续并查集合并
        unordered_map<int, string> acc_idx;         // 邮箱 id -> 账号名
        for (auto& acc : accounts) {
            for (int i=1; i<acc.size(); ++i) {
                string email = acc[i];
                if (!idx_email.count(email)) {
                    idx_email[email] = idx++;
                    acc_idx[idx_email[email]] = acc[0];
                    // acc_idx[idx-1] = acc[0];
                }
            }
        }

        auto uf = UnionFind(idx);   
        for (auto& acc : accounts) {                // 对统一账号下多个邮箱进行合并
            int first = idx_email[acc[1]];
            for (int i = 2; i<acc.size(); ++i) {
                uf.merge(first, idx_email[acc[i]]);
            }
        }

        unordered_map<int, vector<string>> merged; // 将并查集 fid 为关键字合并所有邮箱
        for (auto& [email, id]: idx_email) {
            int fid = uf.find(id);
            if (!merged.count(fid)) {
                merged[fid].push_back(acc_idx[fid]);  // val[0] = account
            }
            merged[fid].push_back(email);
        }
        vector<vector<string>> ans;
        for (auto& [_, val]: merged) {
            sort(val.begin()+1, val.end()); // 邮箱排序
            ans.push_back(val);
        }

        return ans;

    }
};