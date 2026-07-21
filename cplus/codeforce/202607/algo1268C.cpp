#include <bits/stdc++.h>
using namespace std;

template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    FenwickTree(int n) : tree(n + 1) {}
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }
    T query(int l, int r) const {
        if (r < l) return 0;
        return pre(r) - pre(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n;
    cin >> n;
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x] = i;
    }

    FenwickTree<long long> bitCnt(n), bitSum(n);
    vector<long long> f(n + 1);
    long long invCnt = 0;

    for (int k = 1; k <= n; k++) {
        int p = pos[k];
        
        // 1. 新增逆序对：已选位置中比 p 大的个数
        invCnt += bitCnt.query(p + 1, n);
        
        // 2. 插入当前位置
        bitCnt.update(p, 1);
        bitSum.update(p, p);
        
        // 3. 计算聚拢代价
        int target = (k + 1) / 2;
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (bitCnt.pre(mid) >= target) hi = mid;
            else lo = mid + 1;
        }
        int median = lo;
        
        long long cntL = bitCnt.query(1, median - 1);
        long long sumL = bitSum.query(1, median - 1);
        long long cntR = bitCnt.query(median + 1, n);
        long long sumR = bitSum.query(median + 1, n);
        
        // 修正公式：目标位置是从 median - cntL 开始的连续区间
        long long leftCost = cntL * median - cntL * (cntL + 1) / 2 - sumL;
        long long rightCost = sumR - cntR * median - cntR * (cntR + 1) / 2;
        long long gatherCost = leftCost + rightCost;
        
        f[k] = invCnt + gatherCost;
    }

    for (int k = 1; k <= n; k++) {
        cout << f[k] << " \n"[k == n];
    }
    return 0;
}