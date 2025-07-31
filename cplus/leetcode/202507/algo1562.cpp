#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.4 并查集 - 数组上的并查集
class UnionFind {
    vector<int> fa;
    vector<int> cnt;
public:
    UnionFind(int n): fa(n), cnt(n, 1){
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
            fa[x] = y; cnt[y] += cnt[x];
        }
    }

    int count(int x) {
        return cnt[find(x)];
    }
};

class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if (m == n) return m;
        
        vector<int> bin(n+2);
        int ans = -1, m_cnt = 0;
        UnionFind uf(n+1);
        for (int i = 0; i < n; ++i) {
            int x = arr[i];
            bin[x] = 1;
            if (bin[x-1]) {if (uf.count(x-1)==m) m_cnt-=1; uf.merge(x, x - 1);};
            if (bin[x+1]) {if (uf.count(x+1)==m) m_cnt-=1; uf.merge(x, x + 1);};
            if (uf.count(x) == m) m_cnt++;

            if (m_cnt) ans = i+1;
        }
        return ans;
    }
};