#include<bits/stdc++.h>
using namespace std;

// string 算法相关模板
// kmp 
// z function 扩展 kmp



// z 函数 z函数 zfunction z-function z function 模板
// 按思路
auto zFunc_ori = [](string text) -> vector<int> {
    int n = text.size(), l = 0, r = 0;
    vector<int> z(n);
    
    for (int i=1; i<n; i++) {
        if (i <= r) { // z[i] = min(z[i-l], r-i+1) <= 更好
            if (z[i-l] < r - i + 1)
                z[i] = z[i-l];
            else {
                int cur = r - i + 1;
                while (cur + i < n && text[cur] == text[cur+i]) cur ++;
                z[i] = cur;
            }
        } else { // navie
            int cur = 0;
            while (cur + i < n && text[cur] == text[cur+i]) cur ++;
            z[i] = cur;
        }

        if (z[i] + i - 1 > r) l = i, r = z[i] + i - 1;
    }
    return z;
};

// z 函数 z函数 zfunction z-function z function 模板
// 合并类似语句
auto zFunc = [](string text) -> vector<int> {
    int n = text.size(), l = 0, r = 0;
    vector<int> z(n);
    
    for (int i=1; i<n; i++) {
        if (i <= r && z[i-l] < r - i + 1) 
            z[i] = z[i-l];
        else { 
            // z[i] = (i > r ? 0 : r-i+1);
            z[i] = max(0, r-i+1);
            while (z[i] + i < n && text[z[i]] == text[z[i]+i]) z[i] ++;
        }
        if (z[i] + i - 1 > r) l = i, r = z[i] + i - 1;
    }
    return z;
};

int main() {
    vector<int> ans = zFunc("bacabaababbababa");
    for (auto v:ans) cout << v;
    cout << endl;
}