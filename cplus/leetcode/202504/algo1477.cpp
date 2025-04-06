#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        // 参考题解，前缀和 + hash值 + 前后缀分解
        // 两个不相交子数组 -> 前后缀分解
        int n = arr.size();
        vector<int> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + arr[i];
        
        vector<int> suf(n, INT_MAX/2);
        unordered_map<int, int> pos;
        pos[pres[n]] = n;
        for (int i=n-1; i>=0; i--) {
            if (pos.count(pres[i]+target))
                suf[i] = min(pos[pres[i]+target]-i, i+1<n?suf[i+1]:INT_MAX/2);
            pos[pres[i]] = i;
        }
        
        pos.clear();
        pos[0] = 0;
        int ans = INT_MAX/2, pre = INT_MAX/2;
        for (int i=1; i<n; i++) {
            if (pos.count(pres[i]-target)) 
                pre = min(pre, i-pos[pres[i]-target]);
            
            pos[pres[i]] = i;
            ans = min(ans, pre + suf[i]);
        }

        return ans < INT_MAX/2 ? ans : -1;     
    }

    int minSumOfLengths2(vector<int>& arr, int target) {
        // 参考题解，前缀和 + 前后缀分解 + 二分查找
        // 两个不相交子数组 -> 前后缀分解
        int n = arr.size();
        vector<int> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + arr[i];
        
        vector<int> suf(n, INT_MAX/2);

        for (int i=n-1; i>=0; i--) {
            int inx = ranges::lower_bound(pres, pres[i]+target)-pres.begin();
            if (inx<=n && pres[inx] == pres[i]+target)
                suf[i] = min(inx-i, i+1<n?suf[i+1]:INT_MAX/2);
        }
        

        int ans = INT_MAX/2, pre = INT_MAX/2;
        for (int i=1; i<n; i++) {
            int inx = ranges::lower_bound(pres, pres[i]-target)-pres.begin();
            if (inx<=n && pres[inx] == pres[i]-target)
                pre = min(pre, i-inx);
            
            ans = min(ans, pre + suf[i]);
        }

        return ans < INT_MAX/2 ? ans : -1;     
    }    
};