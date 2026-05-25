#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    bool equalFrequency(string word) {
        // 非暴力做法 分类讨论
        vector<int> cnt(26);
        for (auto& ch : word) cnt[ch - 'a'] ++;

        map<int, int> cnt_grp;
        for (auto c : cnt) if (c) cnt_grp[c] ++;

        // 还有不少坑
        if (cnt_grp.size()==1 && (cnt_grp.begin()->first ==1 || cnt_grp.begin()->second ==1)) return true;
        if (cnt_grp.size()==2 && cnt_grp.begin()->first + 1 == next(cnt_grp.begin())->first 
            && next(cnt_grp.begin())->second == 1) return true;
        if (cnt_grp.size()==2 && cnt_grp.begin()->first == 1  && cnt_grp.begin()->second == 1) return true;        
        
        return false; 
    }
};