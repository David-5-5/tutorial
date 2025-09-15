#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        // 自行解答
        stack<int> path; int n = operations.size();

        for (int i=min(49,n-1); i>=0; --i) {
            if (k > (1L<<i)) {
                path.push(i); k -= (1L<<i);
            }
        }

        char ch = 'a';
        while (!path.empty()) {
            auto v = path.top(); path.pop();
            if (operations[v] == 1) {
                ch = 'a' + (ch - 'a' + 1) % 26;
            }
        }
        return ch;
    }
};