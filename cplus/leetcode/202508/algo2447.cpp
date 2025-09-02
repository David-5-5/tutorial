#include <bits/stdc++.h>
using namespace std;

// 位运算 - GCD LogTrick
class Solution {
public:
    int subarrayGCD(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        deque<pair<int, int>> arr_gcd;

        for (int i = 0; i<nums.size(); ++i) {
            for (int j=arr_gcd.size()-1; j>=0; --j) {
                if (arr_gcd[j].first == gcd(arr_gcd[j].first, nums[i])) break;
                arr_gcd[j].first = gcd(arr_gcd[j].first, nums[i]);
            }

            arr_gcd.emplace_back(nums[i], 1);

            auto it = arr_gcd.begin(); auto nxt = it + 1;
            while (it !=arr_gcd.end() && nxt != arr_gcd.end()) {
                
                while (it !=arr_gcd.end() && nxt != arr_gcd.end() && it->first == nxt->first) {
                    nxt->second += it->second;
                    it = next(it); nxt = next(nxt);
                    arr_gcd.erase(prev(it));
                }
                if (it !=arr_gcd.end()) it = next(it);
                if (nxt != arr_gcd.end()) nxt = next(nxt);
            }
            for (auto &[k, v]:arr_gcd) cnt[k] += v;
        }
        return cnt[k]; 
    }
};

int main() {
    vector<int> nums = {9,3,1,2,6,3};
    Solution().subarrayGCD(nums, 3);
}