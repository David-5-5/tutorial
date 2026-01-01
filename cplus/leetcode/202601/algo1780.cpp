#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.7 其他
class Solution {
public:
    bool checkPowersOfThree(int n) {
        // 自行解答
        while (n && (n % 3 == 0 || (n-1) % 3 == 0)) {
            if (n % 3 == 0) n /= 3;
            else n --;
        }

        return n == 0;  
    }
};