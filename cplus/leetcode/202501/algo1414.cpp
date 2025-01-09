#include <bits/stdc++.h>
using namespace std;

const int N = 1e9;
vector<int> fib;
int init = [] {
    fib.push_back(1), fib.push_back(1);
    while (fib[fib.size()-1] < N)
        fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
    return 0;
}();

// 贪心专题 - 其他数学贪心
class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        int ans = 0, inx = fib.size() - 1;
        while (k) {
            while (fib[inx] > k) inx -= 1;
            ans ++, k -= fib[inx];
        }
        return ans;
    }
};