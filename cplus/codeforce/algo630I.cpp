#include <bits/stdc++.h>
using namespace std;

long long combi(int cnt) {
    if (cnt == 0) return 1;
    long long res = 3;
    for (int i=1; i<cnt; i++){
        res *= 4;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    
    long long ans = 0;
    for (int i=0; i<=n-2; i++) {
        ans += combi(i) * combi(n-2-i);
    }
    cout << ans * 4 << endl;
}