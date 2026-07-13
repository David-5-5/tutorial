#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> multiSearch(string big, vector<string>& smalls) {
        auto kmp = [](string str, string pat) -> vector<int> {
            int n = str.size(), m = pat.size();
            vector<int> p_pi(m);
            for (int i=1; i < m; i++) {
                int j = p_pi[i-1];
                while (j > 0 && pat[j]!=pat[i])
                    j = p_pi[j-1];
                if (pat[j] == pat[i])
                    p_pi[i] = j + 1;
                else p_pi[i] = j;
            }

            vector<int> ans;
            int j = 0;
            for (int i=0; i<n; i++) {
                while (j > 0 && str[i] != pat[j])
                    j = p_pi[j-1];
                if (str[i] == pat[j]) j++;
                if (j == m) ans.push_back(i-j+1), j = p_pi[j-1];
            }

            return ans;
        }; 
        
        vector<vector<int>> ans;
        for (auto & s: smalls) {
            if (s.length())
                ans.emplace_back(kmp(big, s));
            else ans.push_back({});
        }
        return ans;
    }
};