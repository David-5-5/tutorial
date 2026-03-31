#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& target) {
        // 阅读理解
        set<int> x_set; int n = nums.size();
        for (int i=0; i<n; i++) if (nums[i]!=target[i]) x_set.insert(nums[i]);
        return x_set.size();
        
    }
};