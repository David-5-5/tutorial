#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 双序列双指针 - 4.1 双指针
class Solution {
public:
    bool canTransform(string start, string result) {
        // 从 python 翻译过来
        int n = start.length();
        int i = 0 , j = 0;
        while (i < n  || j < n) {
            while (i < n && start[i] == 'X') i ++;
            while (j < n && result[j] == 'X') j ++;

            if (i == n || j == n) break;
            
            if (start[i]==result[j] && ((start[i] == 'L' && i >= j) || (start[i] == 'R' && i <= j))) {
                i ++; j ++;
            } else return false;

        }
        return i == j;           
    }
};