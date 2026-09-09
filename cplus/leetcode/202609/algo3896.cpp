#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
bool is_prime[N];
vector<int> primes;
int init = [] {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 2; i < N; ++i) {       // 需要统计质数数量，此处不能筛至平方根
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return 0;
}();


class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0, n = nums.size();
        for (int i=0; i<n; i++) {
            auto it = lower_bound(primes.begin(), primes.end(), nums[i]);
            if (i % 2) {
                if (*it == nums[i]) ans ++;
                if (nums[i] == 2) ans ++;
            } else {
                ans += *it - nums[i];
            }
        }
        return ans;
    }
};