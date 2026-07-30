#include <bits/stdc++.h>
using namespace std;

int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n, m;
    cin >> n >> m;
    vector<long long> balances(n);
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        balances[u-1] -= d; balances[v-1] += d;
    }
    
    vector<vector<long long>> ap, ar;
    for (int i=0; i<n; i++) {
        if (balances[i] > 0) {
            ar.push_back({i, balances[i]});
        } else if (balances[i] < 0) {
            ap.push_back({i, -balances[i]});
        }
    }

    vector<vector<long long>> ans;
    size_t p1 = 0, p2 = 0;
    while (p1 < ap.size() && p2 < ar.size()) {
        if (ap[p1][1] == ar[p2][1]) {
            ans.push_back({ap[p1][0], ar[p2][0], ap[p1][1]});
            p1 ++; p2++;
        } else if (ap[p1][1] > ar[p2][1]) {
            ans.push_back({ap[p1][0], ar[p2][0], ar[p2][1]});
            ap[p1][1] -= ar[p2][1]; p2++;
        } else {
            ans.push_back({ap[p1][0], ar[p2][0], ap[p1][1]});
            ar[p2][1] -= ap[p1][1]; p1 ++; 
        }
    }

    cout << ans.size() << endl;
    for (auto & a: ans) {
        cout << a[0]+1 << " " << a[1]+1 << " " << a[2] << endl;
    }

    return 0;
}

