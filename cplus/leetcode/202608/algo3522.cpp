#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long calculateScore(vector<string>& instructions, vector<int>& values) {
        // 使用 vector 4ms，比较 vector 和 set 性能差异
        long long ans = 0; int i = 0, n = instructions.size(); vector<bool> vis(n);
        while (i>=0 && i < n) {
            if (vis[i]) return ans;
            else vis[i] = true;

            if (instructions[i] == "add") {
                ans += values[i++];
            } else {
                i += values[i];
            }
        }

        return ans;
    }

};
