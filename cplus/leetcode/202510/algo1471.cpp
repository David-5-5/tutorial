#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        // 自行解答
        sort(arr.begin(), arr.end());
        int n = arr.size(), mid = (n-1)/2, l = 0, r = n-1;
        vector<int> ans;
        while (ans.size() < k) {
            if (arr[r]-arr[mid] >= arr[mid]-arr[l]) 
                ans.push_back(arr[r--]);
            else ans.push_back(arr[l++]);
        }
        return ans;
    }
};