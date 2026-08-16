#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        vector<string> res;
        int n = indices.size(), idx[n], ptr = 0;
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return indices[i] < indices[j];
        });
        
        for (int i=0; i<n; i++) {
            int cur = indices[idx[i]];
            if (ptr < cur) {
                res.push_back(s.substr(ptr, cur - ptr));
            }
            auto equals = [&]() -> bool {
                for (int j=0; j<sources[idx[i]].length(); j++) {
                    if (s[cur+j] != sources[idx[i]][j]) return false;
                }
                return true;
            };

            if (equals()) {
                ptr = cur + sources[idx[i]].length(); res.emplace_back(targets[idx[i]]);
            } else if (ptr < cur) ptr = cur;    // 如果不是看到测试案例，这个条件考虑不到
        }
        if (ptr <= s.length()) res.emplace_back(s.substr(ptr));
        
        string ans = "";
        for (auto seg: res) ans += seg;
        return ans;
    }
};

int main() {
    vector<int> indices = {2,2,3};
    vector<string> source = {"cde","cdef","dk"}, target = {"fe","f","xyz"};
    cout << Solution().findReplaceString("abcde", indices, source, target);
}