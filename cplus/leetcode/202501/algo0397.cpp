#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int integerReplacement(int n) {
        // 自行解答
        if (n == 1) return 0;
        if (n == 2) return 1;
        if (n == 3 || n == 4) return 2;

        if (n%2) {
            if ((n-1) % 4) return 2 + integerReplacement(n/2+1); // n = 2^31 -1, n+1溢出
            else  return 2 + integerReplacement(n/2);
        } return 1 + integerReplacement(n/2);   
        
    }

    int integerReplacement(int n) {
        // 参考题解
        if (n == 1) return 0;

        if (n%2) {
            return 2 + min(integerReplacement(n/2+1),integerReplacement(n/2));
        } return 1 + integerReplacement(n/2);
        
    }
};