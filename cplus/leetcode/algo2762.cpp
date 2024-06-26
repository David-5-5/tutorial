#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long continuousSubarrays(vector<int> &nums) {
        int left = 0;
        multiset<int> mset;
        long long  ans = 0;
        for (int right = 0; right < nums.size(); ++right) {
            mset.emplace(nums[right]);
            while (*mset.rbegin() - *mset.begin() > 2) {
                mset.extract(nums[left++]);
            }
            ans += right - left + 1;
        }
        return ans;
    }

    long long continuousSubarrays2(vector<int> &nums) {
        int left = 0;
        multiset<int> mset;
        long long  ans = 0;
        for (int right = 0; right < nums.size(); ++right) {
            mset.insert(nums[right]);
            while (*mset.rbegin() - *mset.begin() > 2) {
                mset.erase(mset.find(nums[left++])); // it will erase the first element which is equal to nums[left]
                // mset.erase(nums[left]));  // it will erase all elements which is equal to nums[left]
            }
            ans += right - left + 1;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,4,2,4};
    cout << sol.continuousSubarrays2(nums) << endl;

    multiset<int> mset = {1,1,1,2,2};
    mset.erase(mset.find(1));
    cout << *mset.begin() << endl;
}