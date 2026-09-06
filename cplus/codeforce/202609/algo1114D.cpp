#include <bits/stdc++.h>
using namespace std;


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n; cin >> n;
    vector<int> nums(n);
    for (int i=0; i<n; i++) cin >> nums[i];
    vector<int> b;
    b.emplace_back(nums[0]);
    for (int i=1; i<n; i++) if (b.back()!=nums[i]) b.emplace_back(nums[i]);
    
    // auto b = nums;
    int m = b.size();

    vector dp(m, vector<int>(m));

    for (int r=1; r<m; r++) {
        for (int l=r-1; l>=0; l--) {
            dp[l][r] = min(dp[l+1][r], dp[l][r-1]) + 1;
            if (b[l] == b[r]) {
                dp[l][r] = dp[l+1][r-1] + 1;
            }
        }
    }

    cout<< dp[0][m-1] << endl;
    return 0;
}

