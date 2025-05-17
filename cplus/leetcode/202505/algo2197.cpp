#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.3 邻项消除
class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        // 自行解答 WA 一次
        int n = nums.size();
        vector<int> ans;

        auto push = [&] (int v) {
            while (ans.size() && gcd(ans.back(), v)>1) {
                v = lcm(v, ans.back());
                ans.pop_back();
            }
            ans.push_back(v);
        };

        int val = nums[0], i=1;
        while (i < n) {
            if (gcd(val, nums[i])>1) {
                val = lcm(val, nums[i++]);
            } else {
                push(val);
                val = nums[i++];
            }
        }
        push(val);
        return ans;
            
    }

    vector<int> replaceNonCoprimes(vector<int>& nums) {
        // 自行解答 直接用栈
        int n = nums.size();
        vector<int> ans;

        for (auto& v : nums) {
            while (ans.size() && gcd(ans.back(), v)>1) {
                v = lcm(v, ans.back());
                ans.pop_back();
            }
            ans.push_back(v);
        }
        return ans;
    }

};