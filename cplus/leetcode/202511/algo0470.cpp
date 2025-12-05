#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
// Only for complication
int rand7() {
    return rand() % 7 + 1; 
}

class Solution {
public:
    int rand10() {
        int num =  (rand7() - 1) * 7 + rand7();
        // 拒绝采样
        while (num > 10) num =  (rand7() - 1) * 7 + rand7();
        return num;
    }

    int rand10() {
        int num =  (rand7() - 1) * 7 + rand7();
        // 拒绝采样 - 优化，截取 1 ~ 40
        while (num > 40) num =  (rand7() - 1) * 7 + rand7();
        return 1 + num%10;
    }
};