#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
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


// 数学算法 - 数论 - 1.2 预处理质数（筛质数）
class Solution {
public:
    long long splitArray(vector<int>& nums) {
        // long long ans = 0; for (auto& val : nums) ans += val;
        long long ans = accumulate(nums.begin(), nums.end(), 0LL);
        int n = nums.size();
        for (int i=0; i<primes.size(); i++) {
            if (primes[i] < n) {
                ans -= 2LL * nums[primes[i]];
            } else break;
        }
        return abs(ans);
    }
};