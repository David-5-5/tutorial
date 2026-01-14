#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int findTheWinner(int n, int k) {
        // 自行解答 模拟
        vector<int> arr(n); iota(arr.begin(), arr.end(), 1);
        int p = 0;

        while (arr.size() > 1) {
            p = (p + k - 1) % arr.size();
            arr.erase(arr.begin() + p);
            p %= arr.size();
        }
        return arr[0];  
    } 

};