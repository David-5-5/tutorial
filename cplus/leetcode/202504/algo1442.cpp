#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        // 自行解答 - 时间复杂度 O(n^2)
        // 计算前缀异或和
        int n = arr.size();
        vector<int> prex(n+1);
        for (int i=0; i<n; i++) prex[i+1] = prex[i] ^ arr[i]; 

        int ans = 0;
        unordered_map<int, int> pos;    // 前缀异或和
        pos[0] ++;                      // 初始前缀为 0
        // 遍历 j，k; i 在 pos 哈希表中查找
        for (int j=1; j<n; j++) {
            for (int k=j; k<n; k++) {
                int target = prex[k+1] ^ prex[j];
                ans += pos[prex[j] ^ target];
            }
            pos[prex[j]] ++; 
        }
        return ans;
    }

};