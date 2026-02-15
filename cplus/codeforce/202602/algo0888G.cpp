#include <bits/stdc++.h>
using namespace std;

const int high = 30;
struct Node {
    Node* son[2]{};
    int cnt = 0;
    unordered_set<int> ids;   // id of cc
};

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
private:
    Node* root = new Node();
    void insert(int val, int id) {
        auto node = root;
        node->cnt ++;
        for (int i=high; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v] == nullptr) node->son[v] = new Node();
            node = node->son[v]; node->cnt ++;
        }
        node->ids.insert(id);
    }

    void remove(int val, int id) {
        auto node = root;
        node->cnt --;
        for (int i=high; i>=0; --i) {
            int v = (val >> i) & 1;
            node = node->son[v]; node->cnt --;
            // if (node->cnt == 0) {delete node; break;}
        }
        node->ids.erase(id);
    }

    pair<int, int> min_xor(int val) {
        int res = 0;
        auto node = root;
        for (int i=high; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v] != nullptr && node->son[v]->cnt) 
                node = node->son[v];
            else if (node->son[v^1] != nullptr && node->son[v^1]->cnt){
                res |= 1 << i; node = node->son[v^1];
            }else return {-1, -1}; // 仅当字典树中元素为空时
        }
        return {res, *node->ids.begin()};
    } 

public:
    long long xorMst(int n, vector<int>& nums) {
        // Boruvka MST
        UnionFind uf(n);
        // key: fa in UnionFind value: vector all x, uf.find(x) == fa
        unordered_map<int, vector<int>> cc; // Connected Component

        for (int i=0; i<n; i++) {
            cc[i].emplace_back(i);  // Each vectex is a cc
            insert(nums[i], i);
        }
        
        long long ans = 0;
        while (cc.size() > 1) {
            unordered_map<int, pair<int, int>> dis; // Each min dis
            for (auto &[x, vert]: cc) {
                for (auto &u: vert) remove(nums[u], u); // delete vectices of cc from Trie
                for (auto &u: vert) {                   // Find min weight to other cc
                    auto cost_v = min_xor(nums[u]);
                    if (!dis.count(x) || dis[x].first > cost_v.first) dis[x] = cost_v;
                }
                for (auto &u: vert) insert(nums[u], u); // insert vertices fo cc into Trie
            }

            // Join the cc
            for (auto &[x, cost_v]: dis) {
                int y = uf.find(cost_v.second);
                if (uf.is_same(x, y)) continue;   // 已经在同一连通块内
                ans += cost_v.first;  
                // 启发式合并
                uf.merge(x, y); cc[y].insert(cc[y].end(), cc[x].begin(), cc[x].end());
                cc.erase(x);    // 移除连通块 x
            }
        }
        
        return ans;
    }
};


int main() {
    int n; cin >> n; vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];

    cout << Solution().xorMst(n, a) << endl;
}