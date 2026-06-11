#include <bits/stdc++.h>
using namespace std;


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mat[i][j];
        }
    }

    int ans = 0;
    for (int j=0; j<m; j++) {
        int res = n;
        // shift记录 值满足 (val-1) % m == j
        //  sf = (n + i - (val-1) / m) % n
        unordered_map<int, int> shift;
        for (int i=0; i<n; i++) {
            auto& val = mat[i][j];
            if ((val-1) % m == j) {
                shift[(n + i - (val-1) / m) % n] ++;
            }
        }

        for (auto [sf, cnt]: shift) {
            res = min(sf + n - cnt, res);
        }
        ans += res;
    }

    cout << ans << endl;
    return 0;
}

