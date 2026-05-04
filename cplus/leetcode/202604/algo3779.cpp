#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.4 逆向思维
class Solution {
public:
    int minOperations(vector<int>& nums) {
        // unordered_set 性能优于 set O(1) < O(logN)
        unordered_set<int> uni_nums; int n = nums.size();
        for (int i=n-1; i>=0; i--) {
            if (!uni_nums.insert(nums[i]).second) {
                return i / 3 + 1;
            }
        }

        return 0;
    }
};