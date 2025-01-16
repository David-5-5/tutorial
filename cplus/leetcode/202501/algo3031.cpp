#include <bits/stdc++.h>
using namespace std;

// 周赛 383
class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        // 参考题解
        auto zFunc = [](string text) -> vector<int> {
            int n = text.size(), l = 0, r = 0;
            vector<int> z(n);
            
            for (int i=1; i<n; i++) {
                if (i <= r && z[i-l] < r - i + 1) 
                    z[i] = z[i-l];
                else { 
                    // z[i] = (i > r ? 0 : r-i+1);
                    z[i] = max(0, r-i+1);
                    while (z[i] + i < n && text[z[i]] == text[z[i]+i]) z[i] ++;
                }
                if (z[i] + i - 1 > r) l = i, r = z[i] + i - 1;
            }
            return z;
        };

        // 对问题的分析能力太弱
        vector<int> zfunc = zFunc(word);
        int n = word.size(),  ans =(n - 1) / k + 1; // 重建字符串的代价
        for (int i=k; i<n; i+=k) {
            if (zfunc[i] + i >=n) {
                ans = min(ans, i/k); break;
            }
        }

        return ans;
    }
};