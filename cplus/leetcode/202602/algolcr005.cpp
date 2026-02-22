#include <bits/stdc++.h>
using namespace std;

// LCR
class Solution {
public:
    int maxProduct(vector<string>& words) {
        // 自行解答 同 318
        int mx = (1 << 26) - 1, n = words.size();
        vector<int> w_chars(n);
        for (int i=0; i<n; ++i) {
            auto m  = words[i].length(); auto& word = words[i];
            for (int j=0; j<m && w_chars[i]<mx; ++j) {
                w_chars[i] |= 1 << (word[j] - 'a');
            }
        }

        int ans = 0;
        for (int i=1; i<n; ++i)  {
            if (w_chars[i] == mx) continue;
            for (int j=0; j<i; ++j) 
                if ((w_chars[i] & w_chars[j]) == 0) 
                    ans = max(ans, (int)(words[i].length() * words[j].length()));
            
        }
        
        return ans;     
    }
};