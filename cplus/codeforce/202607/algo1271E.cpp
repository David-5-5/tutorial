#include <bits/stdc++.h>
using namespace std;

int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    long long n, k;
    cin >> n >> k;

    auto count = [&](long long val) -> long long {
        auto l = val, r = val + ((val % 2) ^ 1);
        long long res = 0;
        while (l <= n) {
            res += min(r, n) - l + 1;   // 分层计算l r 区间的数量
            l *= 2; r = 2 * r + 1;   // 下层区间
        }
        return res;
    };

    auto check = [&](bool even) -> long long {
        long long ans = 0, l = even?2:1, r = n;
        if ((even && r % 2) || (!even && r%2 == 0)) r -= 1;
        while (l<=r) {
            auto mid = (l + r) / 2;
            if ((even && mid % 2) || (!even && mid % 2 == 0)) mid --;
            if (count(mid) >= k) {
                l = mid + 2; ans = mid;
            } else r = mid - 2;
        }

        return ans;
    };


    cout << max(check(true), check(false)) << endl; 

    return 0;
}

