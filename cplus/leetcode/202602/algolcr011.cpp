#include <bits/stdc++.h>
using namespace std;

// 同 525
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + (nums[i]?1:-1);

        
        unordered_map<int, int> pos;
        int ans = 0;
        for (int i=0; i<=n; i++) {
            if (pos.count(pres[i])) ans = max(ans, i - pos[pres[i]]);

            if (!pos.count(pres[i]))  pos[pres[i]] = i; // 记录最靠左值为 pres[i] 下标
        }        
        return ans;        
    }
};