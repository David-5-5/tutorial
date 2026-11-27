#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        // 自行解答，竖式乘法
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int n = num1.length(), m = num2.length();
        vector<vector<int>> partials;

        for (int i=0; i<m; i++) {
            vector<int> row(i);
            int carry = 0;
            
            int x = num2[i] - '0';
            for (int j=0; j<n; j++) {
                int mul = x * (num1[j] - '0');
                row.emplace_back((carry + mul) % 10);
                carry = (carry + mul) / 10;
            }
            if (carry) row.emplace_back(carry);
            partials.emplace_back(row);
        }

        string product;
        auto mx_len = partials[m-1].size(); int carry = 0, mn_r = 0;
        for (int i=0; i<mx_len; i++) {
            auto sum = carry;
            for (int r=mn_r; r<m; r++) {
                if (i >= partials[r].size()) {
                    mn_r = r + 1;
                    continue;
                }
                sum += partials[r][i];
            }
            product += '0' + sum % 10;
            carry = sum / 10;
        }
        while (carry) {
            product += '0' + carry % 10; carry /= 10;
        }
        while (product.length()>1 && product.back() == '0') product.pop_back();
        reverse(product.begin(), product.end());
        return product;

    }

};