#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 双序列双指针 - 4.1 双指针
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        // 自行解答
        int n = s.length(), m = spaces.size(), j=0; string ans = "";
        for (int i=0; i<n; ++i) {
            if (j<m && i == spaces[j]) {
                ans.push_back(' '); j++;
            }
            ans.push_back(s[i]);
        }
        return ans;
    }
    // !!!! OVERTIME !!!!!!
    // string addSpaces(string s, vector<int>& spaces) {
    //     int n = spaces.size();
    //     for (int i=n-1; i>=0; --i) {
    //         s.insert(spaces[i], " ");
    //     }
    //     return s;
    // }
};