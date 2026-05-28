#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    string crackPassword(vector<int>& password) {
        // 自行解答
        sort(password.begin(), password.end(), [&](const int a, const int b){
            return to_string(a) + to_string(b) < to_string(b) + to_string(a);
        });

        string ans = "";
        for (auto w:password) ans += to_string(w);

        return ans;
    }
};