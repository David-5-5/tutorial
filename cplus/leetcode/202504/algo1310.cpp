#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        // 自行解答，前缀异或和 模板题
        int n = arr.size();
        vector<int> prex(n+1);
        for (int i=0; i<n; i++) prex[i+1] = prex[i] ^ arr[i];        

        vector<int> ans;
        for (auto& q: queries) {
            ans.push_back(prex[q[1]+1] ^ prex[q[0]]);
        }
        return ans;
    }
};