#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        // 自行解答
        int n = array.size();
        vector<int> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + (array[i]<"A"?1:-1);
        
        unordered_map<int, int> pos;
        int len = 0, left = 0;
        for (int i=0; i<=n; i++) {
            if (pos.count(pres[i]) && i - pos[pres[i]] > len) {
                len = i - pos[pres[i]];
                left = pos[pres[i]];
            }

            if (!pos.count(pres[i]))  pos[pres[i]] = i; // 记录最靠左值为 pres[i] 下标
        } 

        vector<string> ans;
        for (int i=left; i<left+len; i++) ans.push_back(array[i]);
        return ans;
    }
};