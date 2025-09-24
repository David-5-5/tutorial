#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.1 基础
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        // 滑动窗口 + 前后缀分解
        if (cardPoints.size() == k) return accumulate(cardPoints.begin(), cardPoints.end(), 0);

        int pre = accumulate(cardPoints.begin(), cardPoints.begin()+k, 0);
        int ans = pre, suf = 0, n = cardPoints.size();
        for (int i = 0; i<k; ++i) {
            pre -= cardPoints[k-1-i]; suf += cardPoints[n-1-i];
            ans = max(ans, pre+suf);
        }
        
        return ans;        
    }
};