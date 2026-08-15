#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> domain_cnt;
        for (auto & cpd : cpdomains) {
            size_t pos = cpd.find(' ');
            int cnt = stoi(cpd.substr(0, pos));
            while (pos != string::npos) {
                domain_cnt[cpd.substr(pos+1)] += cnt;
                pos = cpd.find('.', pos+1);
            }
        }

        vector<string> ans;
        for (auto &[domain, cnt] : domain_cnt) {
            ans.emplace_back(to_string(cnt) + " " + domain);
        }

        return ans;
    }
};