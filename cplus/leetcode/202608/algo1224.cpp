#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int, int> elem_cnt, freq_cnt;
        int ans = 2, n = nums.size();

        for (int i=0; i<n; i++) {
            auto & v = nums[i];
            elem_cnt[v] ++;
            freq_cnt[elem_cnt[v]] ++;
            if (elem_cnt[v] - 1) {
                freq_cnt[elem_cnt[v] - 1] --;
                if (freq_cnt[elem_cnt[v] - 1] == 0) freq_cnt.erase(elem_cnt[v] - 1);
            }

            if (freq_cnt.size() == 1 && (freq_cnt.count(1) || freq_cnt[elem_cnt[v]] == 1)) ans = i + 1;
            else if (freq_cnt.size() == 2) {
                if ((freq_cnt.count(1) && freq_cnt[1] == 1) || (freq_cnt[elem_cnt[v]] == 1 && freq_cnt.count(elem_cnt[v]-1)) ||
                (freq_cnt.count(elem_cnt[v]+1) && freq_cnt[elem_cnt[v]+1] == 1)) ans = i + 1;
            }
            
        }
        
        return ans;    
    }
};

int main() {
    vector<int> nums = {1,1,1,2,2,2,3,3,3,4,4,4,5};
    Solution().maxEqualFreq(nums);
}