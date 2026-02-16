#include <bits/stdc++.h>
using namespace std;


// 核心优化1：数组版Trie（缓存友好，无动态内存开销）
const int TRIE_BIT_LEN = 30;
const int MAX_TRIE_NODE = 200000 * TRIE_BIT_LEN + 10; // 预分配足够节点

struct Trie {
    int son[MAX_TRIE_NODE][2]; // 数组代替指针，连续内存
    int tot;                   // 节点计数

    // 构造函数：初始化Trie
    Trie() : tot(0) {
        // 仅初始化根节点（其余节点复用，避免memset开销）
        son[0][0] = son[0][1] = -1;
    }

    // 插入值到Trie（内联函数，减少调用开销）
    inline void put(int32_t v) {
        int node = 0;
        for (int i = TRIE_BIT_LEN - 1; i >= 0; --i) {
            int b = (v >> i) & 1;
            if (son[node][b] == -1) {
                tot++;
                son[tot][0] = son[tot][1] = -1; // 初始化新节点
                son[node][b] = tot;
            }
            node = son[node][b];
        }
    }

    // 查找最小异或值（内联函数）
    inline int min_xor(int32_t v) {
        int res = 0;
        int node = 0;
        for (int i = TRIE_BIT_LEN - 1; i >= 0; --i) {
            int b = (v >> i) & 1;
            if (son[node][b] == -1) {
                res |= 1 << i;
                b ^= 1;
            }
            node = son[node][b];
        }
        return res;
    }

    // 重置Trie（复用节点，避免重复初始化）
    inline void reset() {
        tot = 0;
        son[0][0] = son[0][1] = -1;
    }
};

// 全局变量改为局部（减少缓存失效），用static限制作用域
static long long ans;
static Trie trie; // 复用Trie对象，避免反复构造析构

// 核心优化2：分治函数（传引用+减少拷贝，inline递归）
inline void dfs(vector<int32_t>& a, int p) {
    if (a.empty() || p < 0) return;

    // 优化：预分配数组空间，减少push_back扩容
    vector<int32_t> b[2];
    b[0].reserve(a.size());
    b[1].reserve(a.size());

    for (int32_t v : a) {
        int k = (v >> p) & 1;
        b[k].push_back(v);
    }

    if (!b[0].empty() && !b[1].empty()) {
        trie.reset(); // 复用Trie，无需重建
        for (int32_t v : b[0]) {
            trie.put(v);
        }
        int res = INT_MAX;
        for (int32_t v : b[1]) {
            res = min(res, trie.min_xor(v));
        }
        ans += res;
    }

    dfs(b[0], p - 1);
    dfs(b[1], p - 1);
}

int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n;
    cin >> n;
    vector<int32_t> a(n);
    // 优化：直接读取原始数据，减少中间拷贝
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ans = 0;
    dfs(a, 29);

    cout << ans << endl;

    return 0;
}