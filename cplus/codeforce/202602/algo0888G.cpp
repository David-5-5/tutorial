#include <bits/stdc++.h>
using namespace std;

const int high = 29;

const int MAX_TRIE_NODE = 30 * 200000 + 10;

struct Node {
    int son[2];  // int索引代替指针，消除动态内存开销
    int cnt = 0;
    int id = -1;
    Node() { son[0] = son[1] = -1; }
} trie[MAX_TRIE_NODE];
int trie_idx = 0;

class UnionFind {                   // 并查集模板
    vector<int> fa;
public:
    UnionFind(int n): fa(n) {
        iota(fa.begin(), fa.end(), 0);
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
    void resetRoot() {
        trie_idx = 0;
        trie[trie_idx] = Node();
    }
    void insert(int val, int id) {
        int node = 0;
        trie[node].cnt ++;
        for (int i=high; i>=0; --i) {
            int v = (val >> i) & 1;
            if (trie[node].son[v] == -1) {
                trie_idx++;
                trie[trie_idx] = Node();
                trie[node].son[v] = trie_idx;
            }
            node = trie[node].son[v];
            trie[node].cnt ++;
        }
        trie[node].id = id;
    }

    void remove(int val) {
        int node = 0;
        trie[node].cnt --;
        for (int i=high; i>=0; --i) {
            int v = (val >> i) & 1;
            node = trie[node].son[v];
            trie[node].cnt --;
        }
    }

    pair<int, int> min_xor(int val) {
        int res = 0;
        int node = 0;
        for (int i=high; i>=0; --i) {
            int v = (val >> i) & 1;
            if (trie[node].son[v] != -1 && trie[trie[node].son[v]].cnt) 
                node = trie[node].son[v];
            else if (trie[node].son[v^1] != -1 && trie[trie[node].son[v^1]].cnt){
                res |= 1 << i; 
                node = trie[node].son[v^1];
            }else return {-1, -1};
        }
        return {res, trie[node].id};
    } 

public:
    long long xorMst(int n, vector<int>& nums) {
        // Boruvka MST
        UnionFind uf(n);
        // key: fa in UnionFind value: vector all x, uf.find(x) == fa
        unordered_map<int, list<int>> cc; // Connected Component
        unordered_map<int, int> w2id;
        resetRoot(); 
        for (int i=0; i<n; i++) {
            if (w2id.count(nums[i])) {
                auto x = w2id[nums[i]]; // x is id of cc
                // cc[x].emplace_back(i);  // Each vectex is a cc
                uf.merge(i, x);
            } else {
                w2id[nums[i]] = i; cc[i].emplace_back(i);  // Each vectex is a cc
                insert(nums[i], i);
            }
        }
        
        long long ans = 0;
        while (cc.size() > 1) {
            unordered_map<int, pair<int, int>> dis; // Each min dis
            for (auto &[x, vert]: cc) {
                for (auto &u: vert) remove(nums[u]); // delete vectices of cc from Trie
                for (auto &u: vert) {                   // Find min weight to other cc
                    auto weight = min_xor(nums[u]);
                    if (!dis.count(x) || dis[x].first > weight.first) dis[x] = weight;
                }
                for (auto &u: vert) insert(nums[u], u); // insert vertices fo cc into Trie
            }

            // Join the cc
            for (auto [x, weight]: dis) {
                int y = uf.find(weight.second);
                if (!cc.count(x) || uf.is_same(x, y)) continue;   // It's same
                ans += weight.first;  
                // Merge
                uf.merge(x, y); cc[y].splice(cc[y].end(), cc[x]);
                cc.erase(x);    // 移除连通块 x
            }
        }
        
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n; vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];

    cout << Solution().xorMst(n, a) << endl;
}