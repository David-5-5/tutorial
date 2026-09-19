#include <bits/stdc++.h>
using namespace std;


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n; cin >> n;
    string s; cin >> s;

    // 表示 f[i] 第 1～i 个字符需要最少删除次数，转移来源
    // f[i] = f[i-1] + 1        # 直接删除
    // f[i] = f[i0-1] + f[last] - 
    vector dp(n, vector<int>(n+1));
    
    for (int i=0; i<n; i++) dp[i][i] = 1;
    for (int r=1; r<n; r++) {
        for (int l=0; l<r; l++) {
            dp[l][r] = dp[l][r-1] + 1;
            for (int k=r-1; k>=l; k--) {
                if (s[k] == s[r]) {
                    dp[l][r] = min(dp[l][r], dp[l][k] + ((k+1<=r-1)?dp[k+1][r-1]:0));
                }
            }
        }
    }

    cout<< dp[0][n-1] << endl;
    return 0;
}

