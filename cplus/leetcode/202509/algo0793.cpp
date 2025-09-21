#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.4 阶乘分解
class Solution {
public:
    int preimageSizeFZF(int k) {
        // 暴力 - O(N)
        int tot = 0;
        long long i = 5;
        while(true) {  
            if (tot == k) return 5;
            if (tot > k) return 0;            
            auto comp = i;
            while (comp % 5 == 0) {
                comp /= 5;
                tot ++;
            }
            i += 5;
        }
    }


};