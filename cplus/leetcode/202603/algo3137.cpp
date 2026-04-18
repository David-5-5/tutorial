#include <bits/stdc++.h>
using namespace std;

// 顺序做题
class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        // 自行解答
        unordered_map<string, int> cnt;
        int n = word.length(), ans = 0;
        for (int i=0; i<n; i+=k) {
            cnt[word.substr(i, k)] ++;
            ans = max(ans, cnt[word.substr(i, k)]);
        }

        return n / k - ans;
    
    }
};