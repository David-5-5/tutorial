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

    int findTheWinner2(int n, int k) {
        // 参考题解 数学 约瑟夫环 f(n) = (k + f(n-1)-1) % n + 1
        int winner = 1;
        for (int i = 2; i<=n; i++) winner = (k + winner - 1) % i + 1;

        return winner;
    }
};