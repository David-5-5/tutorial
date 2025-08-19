#include <bits/stdc++.h>
using namespace std;

// 二叉树 - 2.16 其他
class Solution {
public:
    bool isValidSerialization(string preorder) {
        // 参考豆包
        istringstream iss(preorder); string node;
        int slots = 1;  // 可用槽位数量, 初始化
        while (getline(iss, node, ',')) {
            slots --; // 每个节点消耗一个槽位
            if (slots < 0) return false;

            if (node != "#") slots += 2;
        }
        return slots == 0;
    }


};