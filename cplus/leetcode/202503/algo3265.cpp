#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
// 3267 中等难度版本
class Solution {
public:
    int countPairs(vector<int>& nums) {
        // 自行解答，觉得代码写的特别烂
        unordered_map<int, int> cnt;
        int ans = 0;
        for (auto v:nums) {
            ans += cnt[v];
            string sv = "0000000" + to_string(v);
            for (int i=1; i<sv.length(); i++) {
                for (int j=0; j<i; j++) {
                    if (sv[i] != sv[j]) {
                        string nv = sv;
                        nv[i] = sv[j];
                        nv[j] = sv[i];
                        ans += cnt[atoi(nv.c_str())];
                    }
                }
            }

            cnt[v] ++;
        }
        return ans;    
    }
};