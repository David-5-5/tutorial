#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        // 自行解答 进位法
        if (arr1.size() < arr2.size()) swap(arr1, arr2);
        int n = arr1.size();
        reverse(arr1.begin(), arr1.end());
        reverse(arr2.begin(), arr2.end());

        for (int i=0; i<arr2.size(); i++) {
            arr1[i] += arr2[i];
        }

        arr1.push_back(0); arr1.push_back(0);
        for (int i=0; i<n; i++) {
            while(arr1[i] > 1) {
                arr1[i] -= 2;
                if (arr1[i+1]) arr1[i+1] -= 1;      // 上位负数，进行抵消
                else arr1[i+1] +=1, arr1[i+2] += 1; 
            }
        }

        while (arr1.size() && arr1.back() == 0) {    // 去除前导 0
            arr1.pop_back();
        }

        if (arr1.empty()) return {0};
        
        reverse(arr1.begin(), arr1.end());
        return arr1;  
    }
};
