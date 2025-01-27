#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他
class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        // 自行解答，分情况讨论
        int mn = min(a, min(b, c)), mx = max(a, max(b, c));
        // 连续的情况
        if (mn + 2 == mx) return {0, 0};

        int mid = a;
        if (b != mn && b!=mx) mid = b;
        else if (c!=mn && c!= mx) mid = c;
        // 非连续的情况最小值为有两个连续或仅一个空的情况下为 1，其他为2
        // 最大值，[mn..mx]之间的不包括 mid 的所用空位 
        return {max(1, min(2, min(mid-mn-1, mx-mid-1))), mx-mn-2};    
    }
};