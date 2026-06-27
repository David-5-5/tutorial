#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        auto dfs = [&](this auto&& dfs, int l, vector<int>& a, vector<int>& b, vector<int>& c) -> void {
            if (l == 1) {c.push_back(a.back()); a.pop_back();}
            else {
                dfs(l-1, a, c, b);
                c.push_back(a.back()); a.pop_back();
                dfs(l-1, b, a, c);
            }
        };

        dfs(A.size(), A, B, C);
    }

};