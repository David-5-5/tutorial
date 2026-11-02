#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int passwordStrength(string password) {
        unordered_set<int> lowers, uppers, digits, specs;
        int ans = 0;
        for (auto & ch: password) {
            if (ch>='a' && ch<='z') {
                if (lowers.emplace(ch).second) ans += 1;
            } else if (ch>='A' && ch <='Z') {
                if (uppers.emplace(ch).second) ans += 2;
            } else if (ch>='0' && ch<='9') {
                if (digits.emplace(ch).second) ans += 3;
            } else {
                if (specs.emplace(ch).second) ans += 5;
            }
        }

        return ans;        
    }
};