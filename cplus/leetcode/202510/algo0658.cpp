#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // 自行解答，这个代码很优雅
        auto right = upper_bound(arr.begin(), arr.end(), x);
        // 技巧 begin() end() 的差异，
        // 由于 begin() 是第一个元素，end() 是末尾的空元素
        // 因此 left 取的是前一个元素prev(left) ，right取的是当前元素
        auto left = right;  // 初始情况left和right指向同一个元素
        deque<int> ans;
        while (ans.size() < k) {
            if (left == arr.begin()) ans.insert(ans.end(), right, right+k-ans.size());
            else if (right == arr.end()) ans.insert(ans.begin(), left-k+ans.size(), left);
            else {
                if (x - *prev(left) <= *right-x) {
                    ans.push_front(*prev(left)); left = prev(left);
                } else {
                    ans.push_back(*right); right = next(right);
                }
            }

        }
        return vector<int>(ans.begin(), ans.end());
    }
};