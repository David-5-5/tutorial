#include <bits/stdc++.h>
using namespace std;


// 数学算法 - 数论 - 1.4 阶乘分解
class Solution {
public:
    int trailingZeroes(int n) {
        // 自行解答 O(N)
        int tot = 0;
        for (int i = 5; i <=n; i+=5) {      
            int comp = i;
            while (comp % 5 == 0) {
                comp /= 5;
                tot ++;
            }
        }
        return tot;
    }

    int trailingZeroes2(int n) {
        // 参考题解
        // int tot = 0, p = 5;
        // while (p < n) {
        //     tot += n / p;
        //     p *= 5;
        // }

        // return tot;
        
        // 另一种写法
        int tot = 0;
        while (n) {
            n /= 5;
            tot += n;
        }

        return tot;

    }

};