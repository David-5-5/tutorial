#include <bits/stdc++.h>
using namespace std;

const int MX = 32000;
vector<int> primes;
auto init = [] {
    vector<bool> is_primes(MX, true);
    // is_primes[0] = false; is_primes[1] = false;
    for (int i=2; i<MX; i++) {
        if (!is_primes[i]) continue;
        for (int j=i*i; j<MX; j+=i) {
            is_primes[j] = false;
        }
    }

    for(int i=2; i<MX; ++i) {
        if (is_primes[i]) primes.emplace_back(i);
    }
    return 0;
}();

int Omega(long long val) {
    if (val == 1) return 0;
    int cnt = 0;
    for (auto& f: primes) {
        if (val == 1) break;
        while (val % f == 0) {
            cnt += 1;
            val /= f;
        }
    }
    if (val != 1) return cnt + 1;
    else return cnt;
};

void divide(int& a, int& b, int& k) {
    int mn = 2, mx = 0;
    if (a == b) mn = 0;
    else if (b % a == 0) mn = 1;
    
    mx = Omega(a) + Omega(b);
    // if (k >= mn && k <= mx && (a != b || k%2 == 0))
    if (k >= mn && k <= mx && (k!=1 || (k==1 && mn==1)))
        cout << "YES" << endl;
    else cout << "NO"  << endl;

};

int main() {
    int t;
    cin >> t;

    for (int i=0; i<t; ++i) {
        int a, b, k; 
        cin >> a >> b >> k;
        if (a<=b)
            divide(a, b, k);
        else divide(b, a, k);
    }
}