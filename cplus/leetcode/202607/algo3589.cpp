#include <bits/stdc++.h>
using namespace std;

const int N = 50001;
bool is_prime[N];
int init = [] {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 2; i < N; ++i) {       // 需要统计质数数量，此处不能筛至平方根
        if (is_prime[i]) {
            for (long long j = 1LL * i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return 0;
}();


class Solution {
public:
    int primeSubarray(vector<int>& nums, int k) {
        int n = nums.size();

        multiset<int> p_cnt; int last[2]= {-1, -1}, ans = 0;
        int l = 0;
        for (int r = 0; r < n; r++) {
            if (is_prime[nums[r]]) {
                p_cnt.insert(nums[r]); last[0] = last[1], last[1] = r;
            }
            while (l < r && p_cnt.size() && *p_cnt.rbegin() - *p_cnt.begin() > k) {
                if (is_prime[nums[l]]) {
                    auto it = p_cnt.find(nums[l]); p_cnt.erase(it);                  
                }
                l ++;
            }
            if (p_cnt.size() >= 2) {
                ans += last[0] - l + 1;
            }
        }

        return ans;
    }

    int primeSubarray2(vector<int>& nums, int k) {
        int n = nums.size();

        auto count = [&](int d) -> int {
            multiset<int> p_cnt; int ans = 0;
            int l = 0;

            for (int r = 0; r < n; r++) {
                if (is_prime[nums[r]]) {
                    p_cnt.insert(nums[r]);
                }
                auto check = [&]() -> bool {
                    if (!is_prime[nums[l]]) return true;
                    if (d == 0 && p_cnt.size() > 2) return true;
                    if (p_cnt.size() > 2 && *p_cnt.begin() != nums[l] && *p_cnt.rbegin() != nums[l]) return true;
                    if (p_cnt.size() > 2 && *p_cnt.begin() == nums[l] &&  
                        (nums[l] == *next(p_cnt.begin()) || *p_cnt.rbegin()-*next(p_cnt.begin()) >=d ))
                        return true;
                    if (p_cnt.size() > 2 && *p_cnt.rbegin() == nums[l] &&  
                        (nums[l] == *prev(p_cnt.rbegin()) || *prev(p_cnt.rbegin()) - *p_cnt.begin() >=d ))
                        return true;
                    return false;
                };
                while (check()) {
                    if (is_prime[nums[l]]) {
                        auto it = p_cnt.find(nums[l]); p_cnt.erase(it);
                    }
                    l ++;
                }
                if (p_cnt.size() >= 2 && *p_cnt.rbegin() - *p_cnt.begin() >=d) ans += l+1;
             }
            return ans;
        };
        
        return count(0) - count(k+1) ;
    }    
};