#include <bits/stdc++.h>
using namespace std;

// 周赛 379
class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答，练习 set 使用
        int n = nums1.size();

        // compare to unordered_set
        set<int> s1(nums1.begin(), nums1.end());
        set<int> s2(nums2.begin(), nums2.end());

        if (s1.size() < s2.size()) {
            set<int> tmp = s1;
            s1 = s2;
            s2 = tmp;
        }

        set<int> diff;
        // it is wrong for {1,2} - {1} for unordered_set
        set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), 
            inserter(diff, diff.begin()));

        int ans = min(int(diff.size()), n/2) + s2.size();

        if (ans < n) return ans;
        else return n;

    }
};