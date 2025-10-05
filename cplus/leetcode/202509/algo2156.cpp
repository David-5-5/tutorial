#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        // 自行解答 
        // 倒序遍历和字符串hash一致，一边计算hash，一边计算 power^(k-1) 次幂，不需要快速幂
        int pk = 1, hash = 0, n = s.length(); string ans = "";
        for (int i=n-1; i>n-k; --i) {
            hash = (1L * hash * power % modulo + (s[i]-'a'+1)) % modulo;
            pk = 1L * pk * power % modulo;
        }

        for (int i=n-k; i>=0; --i) {
            hash = (1L * hash * power % modulo + (s[i]-'a'+1)) % modulo;
            if (hash == hashValue) ans = s.substr(i, k);
            hash = ((hash - 1L * (s[i+k-1]-'a'+1) * pk % modulo) % modulo + modulo) % modulo;
        }

        return ans;   
        
    }
};