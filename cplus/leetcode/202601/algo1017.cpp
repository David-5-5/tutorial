#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    string baseNeg2(int n) {
        // 自行解答 进位法
        if (n == 0) return "0";

        vector<int> binary(33, 0);
        for (int i=0; i<32; i++) {
            if ((n >> i) & 1) {
                if (i % 2) binary[i] += 1, binary[i+1] += 1;
                else binary[i] += 1;
            }
        }
        for (int i=0; i<32; i++) {
            while(binary[i] > 1) {
                binary[i] -= 2;
                if ((i+1) % 2) 
                    if (binary[i+1]) binary[i+1] -= 1;      // 上位负数，进行抵消
                    else binary[i+1] +=1, binary[i+2] += 1; 
                else binary[i+1] += 1;
            }
        }

        while (binary.back() == 0) {    // 去除前导 0
            binary.pop_back();
        }

        string ans;
        for (int i=binary.size()-1; i>=0; --i) ans += '0' + binary[i];
        return ans;    
    }
};
