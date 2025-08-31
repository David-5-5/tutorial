#include <bits/stdc++.h>
using namespace std;

// 位运算 - 异或（XOR）的性质
class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        // 参考题解
        int n = encoded.size() + 1, tot = 0, ex_0 = 0;
        // 1~n 的异或和
        for (int i=1; i<=n; ++i) tot ^= i;
        // 除perm[0] 之外，其他 n-1 个元素的异或和
        for (int i=1; i<n-1; i+=2) {
            ex_0 ^= encoded[i];
        }
        vector<int> perm(n); perm[0] = tot ^ ex_0;
        for (int i=0; i<n-1; ++i) perm[i+1] = perm[i] ^ encoded[i];
        return perm;
    }
};