#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSpecialEquivGroups(vector<string>& words) {
        set<string> seen; int n = words[0].length();
        for (auto word : words) {
            string even = "", odd = "";
            for (int i=0; i<n; i++) {
                if (i % 2) odd.push_back(word[i]);
                else even.push_back(word[i]);
            }
            sort(odd.begin(), odd.end()); sort(even.begin(), even.end());
            seen.insert(even + odd);
        }
        return seen.size();
    }
};