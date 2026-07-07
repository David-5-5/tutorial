#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> statisticalResult(vector<int>& arrayA) {
        int len = arrayA.size();
        if(len == 0) return {};
        vector<int> arrayB(len, 1);
        arrayB[0] = 1;
        int tmp = 1;
        for(int i = 1; i < len; i++) {
            arrayB[i] = arrayB[i - 1] * arrayA[i - 1];
        }
        for(int i = len - 2; i >= 0; i--) {
            tmp *= arrayA[i + 1];
            arrayB[i] *= tmp;
        }
        return arrayB;
    }
};