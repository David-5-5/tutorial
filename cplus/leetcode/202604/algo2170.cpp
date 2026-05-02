#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        map<int, int> odd, even;
        for (int i = 0; i<n; ++i) {
            if (i % 2) odd[nums[i]] ++;
            else even[nums[i]] ++;
        }

        int odd_max_cnt = 0, even_max_cnt = 0;
        int odd_sec_cnt = 0, even_sec_cnt = 0;
        int odd_mx = 0, even_mx = 0;

        for (auto &[val, cnt] : odd) {      // 找出最大及次大频率
            if (cnt > odd_max_cnt) {
                odd_mx = val; odd_sec_cnt = odd_max_cnt;
                odd_max_cnt = cnt;
            } else if (cnt > odd_sec_cnt) odd_sec_cnt = cnt;
        }

        for (auto &[val, cnt] : even) {
            if (cnt > even_max_cnt) {
                even_mx = val; even_sec_cnt = even_max_cnt;
                even_max_cnt = cnt;
            } else if (cnt > even_sec_cnt) even_sec_cnt = cnt;
        }
     
        if (odd_mx != even_mx) return n - odd_max_cnt - even_max_cnt;
        else return n - max(odd_max_cnt - even_sec_cnt, odd_sec_cnt + even_max_cnt);
    }
};
