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

    string multiply2(string num1, string num2) {
        // 性能优化版本
        if (num1 == "0" || num2 == "0") return "0";
        
        int n = num1.size(), m = num2.size();
        // 结果最大长度为 n + m，直接预分配避免扩容
        vector<int> res(n + m, 0);
        
        // 逆序遍历，直接累加到目标位置，避免存储 partials
        for (int i = n - 1; i >= 0; --i) {
            int d1 = num1[i] - '0';
            for (int j = m - 1; j >= 0; --j) {
                int d2 = num2[j] - '0';
                int pos = i + j + 1; // 精准定位
                int sum = res[pos] + d1 * d2;
                
                res[pos] = sum % 10;
                res[pos - 1] += sum / 10; // 进位直接叠加，后续循环会处理
            }
        }
        
        // 一次性转换为字符串，跳过前导零
        string product;
        product.reserve(n + m);
        int idx = 0;
        while (idx < res.size() && res[idx] == 0) ++idx;
        for (; idx < res.size(); ++idx) {
            product.push_back('0' + res[idx]);
        }
        
        return product.empty() ? "0" : product;

    }    
};