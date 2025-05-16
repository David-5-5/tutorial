#include <bits/stdc++.h>
using namespace std;

const int N = 400005;
long long theta[N];
long long Theta[N+1]{0};

auto init = []() {
    iota(theta, theta+N, 0);

    for (int i=2; i<=N; ++i) {
        if (theta[i] == i) {
            for (int j=i; j<N; j+=i)
                theta[j] = theta[j]*(i-1)/i ;
        }
    }
    for (int i=1; i<N; i++) Theta[i+1] = theta[i] + Theta[i];

    return 0;
}();


// 后缀求和 ，未用到 abel 求和
long long solution(int n) {
    if (n==1) return 0;
    return Theta[n] <<1 | 1;

};

int main()
{
    int n;
    cin >> n;
    cout << solution(n) << endl;
    return 0;
}