#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string, vector<int>> records;
        
        int n = keyName.size();
        for (int i=0; i<n; i++) {
            int kt = stoi(keyTime[i].substr(0, 2)) * 60 + stoi(keyTime[i].substr(3));
            records[keyName[i]].emplace_back(kt);
        }
        vector<string> ans;
        for (auto &[name, times]: records) {
            sort(times.begin(), times.end());
            if (times.size()<3) continue;
            for (int i=0; i < times.size()-2; i++) {    // times.size() 是无符号整数 
                if (times[i+2] <= times[i] + 60) {ans.emplace_back(name); break;}
            }
        }

        // sort, distinct
        sort(ans.begin(), ans.end());
        return ans;  
    }    
};