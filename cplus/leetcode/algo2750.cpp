#include <bits/stdc++.h>
using namespace std;

long long mod = 1e9 + 7;
class Solution {
public:
    int numberOfGoodSubarraySplits(vector<int>& nums) {
        long long ans = 0;
        int prev = -1;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                if (prev == -1) {
                    ans = 1;
                } else {
                    ans = (ans * (i - prev)) % mod;
                }
                prev = i;
            }
        }
        return ans % mod;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {0,1,1,1,0,0,1,1,0,0,1};

    cout << solution.numberOfGoodSubarraySplits(nums) << endl;
}