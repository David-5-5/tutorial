#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int reinitializePermutation(int n) {
        // 任一非端点元素，模拟转移的路径
        int i = 1, step = 0;
        while (true) {
            step ++;
            if (i % 2) i = n / 2 + (i-1)/2;
            else i = i / 2;

            if ( i== 1) return step;
        }

        return -1;
    }
}; 