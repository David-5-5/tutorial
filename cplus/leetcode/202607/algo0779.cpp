#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthGrammar(int n, int k) {
        auto dfs = [] (this auto&& dfs, int n, int bit, int k) -> int {
            if (n == 1) return bit;
            int p = pow(2, n-2);
            if (k > p) return dfs(n-1, bit^1, k-p); // in right child of root
            else return dfs(n-1, bit, k);           // in left child of root
        };

        return dfs(n, 0, k);
    }


};