#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 扩展
class Solution {
public:
    int longestWPI(vector<int>& hours) {

        // 递减队列，二分查找
        vector<pair<int, int>> dec;

        auto binary_search_le = [&](int target) {
            int left = 0, right = dec.size() - 1;
            int result = -1;  // 初始化为未找到
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                
                if (dec[mid].first < target) {
                    result = mid;        // 记录当前可能的答案
                    right = mid - 1;     // 继续向左查找更小的索引
                } else {
                    left = mid + 1;      // 向右查找
                }
            }
            
            return result;
        };
        dec.push_back({0, 0});
        
        int ans = 0, n = hours.size(), pres = 0;
        for (int i=0; i<n; ++i) {
            pres += hours[i]>8? 1 : -1;
            int j = binary_search_le(pres);
            if (j != -1)  {
                ans = max(ans, i + 1 - dec[j].second);
            }
            if (pres < dec.back().first)  dec.push_back({pres, i+1});
        }

        return ans;
    }
};