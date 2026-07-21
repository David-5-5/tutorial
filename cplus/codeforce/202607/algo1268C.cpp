#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.2 树状数组和线段树 - 逆序对
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}
    // a[i] 增加 val, 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    // 求前缀和 a[1] + ... + a[i] 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res += tree[i];
        }
        return res;
    }
    // 求区间和 a[l] + ... + a[r], 1 <= l <= r <= n
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }    
};


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    long long n;
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];
    int idx[n];
    iota(idx, idx+n, 0);
    sort(idx, idx + n, [&](int i, int j) {
        return arr[i] < arr[j];
    });

    FenwickTree<int> ft(n);
    vector<int> ans(n);
    ft.update(1, 1);
    auto l = idx[0], r = idx[0];
    for (int i=1; i<n; i++) {
        auto pos = idx[i];
        if (pos >= l && pos <= r) continue; // 区间内已遍历
        if (pos < l) {
            for (int j=l-1; j>=pos; j--) {
                auto & x = arr[j];
                ans[x-1] = ft.pre(x);
                ft.update(x, 1);
            }
            l = pos;
        } else {
            for (int j=r+1; j<=pos; j++) {
                auto & x = arr[j];
                ans[x-1] = ft.query(x, n);
                ft.update(x, 1);
            }
            r = pos;
        }
    }
    int pres = 0;
    for (int i=0; i<n; i++) {
        pres += ans[i];
        cout << pres << " ";
    }
    cout << endl;
    return 0;
}

