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

    int kthGrammar2(int n, int k) {
        if (n == 1) return 0;
        
        // father ： kthGrammar(n-1, (k+1)/2) 
        // left child == father        , k is odd
        // right child == 1 ^ father   , k is even 
        return (k&1) ^ 1 ^ kthGrammar(n-1, (k+1)/2);
    }    
};