#include <bits/stdc++.h>
using namespace std;


int main() {

    const int mod = 1e9 + 7;

    string s, t; 
    cin >> s >> t;

    int n = s.length();

    vector<long long> dp(n+1), val(n+1), sum(n+1);
    auto kmp = [&](string str, string pat) -> void {
        int n = str.size(), m = pat.size();
        vector<int> p_pi(m);
        for (int i=1; i < m; i++) {
            int j = p_pi[i-1];
            while (j > 0 && pat[j]!=pat[i])  j = p_pi[j-1];
            if (pat[j] == pat[i]) p_pi[i] = ++j;
        }

        int j = 0;
        for (int i=0; i<n; i++) {
            while (j > 0 && str[i] != pat[j]) j = p_pi[j-1];
            if (str[i] == pat[j]) j++;
            if (j == m) val[i+1] = i-j+2, j = p_pi[j-1];
            else val[i+1] = val[i];
        }

    };
    kmp(s, t);
    for (int i=1; i<=n; ++i) {
        dp[i] = (dp[i-1] + (val[i]?(sum[val[i]-1] + val[i])%mod:0)) % mod;
        sum[i] = (sum[i-1] + dp[i]) % mod;
    }

    cout << dp[n] << endl; 
    return 0;
}
