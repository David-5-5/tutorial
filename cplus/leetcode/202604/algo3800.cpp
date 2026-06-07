#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
        int cnt0 = 0, cnt1 = 0, n = s.length();
        for (int i=0; i<n; ++i) {
            if (s[i] != t[i]) {
                if (s[i] == '0') cnt0 ++;
                else cnt1 ++;
            }
        }
        
        // cnt0 < cnt1
        if (cnt0 > cnt1) swap(cnt0, cnt1); 

        long long res1 = 1LL * (cnt0 + cnt1) * flipCost; // flip
        long long swap = 1LL * cnt0 * swapCost;          //  swap cnt0 个数字 cnt0 * 2 组 相同
        // swap 后有两种方式：
        long long left_flip = 1LL * (cnt1 - cnt0) * flipCost; // 1： 剩余的flip
        // 两两执行 swap + cross， 如果剩余单个不相同数，必须执行flip
        long long left_all = 1LL * (cnt1-cnt0)/2 * (swapCost + crossCost) + ((cnt1-cnt0)%2?flipCost:0) ; 

        return min(res1, min(swap + left_flip, swap + left_all));  
    }
};