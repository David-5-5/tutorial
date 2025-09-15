#include <bits/stdc++.h>
using namespace std;

const int N = 100+1;
bool is_prime[N];
int init = [] {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 2; i <= sqrt(N); ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return 0;
}();


// 数学算法 - 数论 - 1.1 判断质数
class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        int prev = -1, ans = 0;
        for (int i=0; i<nums.size(); ++i) {
            if (is_prime[nums[i]]) {
                if (prev == -1) prev = i;
                else ans = max(ans, i - prev);
            }
        }
        return ans;
    }

    int maximumPrimeDifference2(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            if (!is_prime[nums[i]]) i++;
            else if (!is_prime[nums[j]]) j--;
            else return j - i;
        }
        return 0;
    }

    int maximumPrimeDifference3(vector<int>& nums) {
        auto isprime = [] (int val) -> bool {
            for (int i=2; i*i<=val; ++i) {
                if (val % i== 0) return false;
            }
            return val>=2;
        };

        int i = 0, j = nums.size() - 1;
        while (i < j) {
            if (!isprime(nums[i])) i++;
            else if (!isprime(nums[j])) j--;
            else return j - i;
        }
        return 0;
    }      
};