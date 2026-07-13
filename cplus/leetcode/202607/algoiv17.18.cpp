#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestSeq(vector<int>& big, vector<int>& small) {
        // sliding windows
        unordered_set<int> small_hash(small.begin(), small.end());
        unordered_map<int, int> cnt; vector<int> ans;
        int l = 0, n = big.size(), m = small.size(); 
        for (int r = 0; r < n; r++) {
            if (small_hash.count(big[r])) cnt[big[r]] ++;

            while (l < r && (!small_hash.count(big[l]) || cnt.count(big[l]) && cnt[big[l]] > 1 )){
                if (cnt.count(big[l]) && cnt[big[l]] > 1) cnt[big[l]] --;
                l ++;
            }

            if (cnt.size() == m) {
                if (ans.size() == 0 || ans[1] - ans[0] > r - l) ans = {l, r};
            }
        }

        return ans;    
    }
};