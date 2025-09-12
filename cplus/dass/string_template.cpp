#include<bits/stdc++.h>
using namespace std;

// string 算法相关模板
// kmp
// 参数 str 字符串 pat 模式串
// 返回 vector<int> str 中匹配 pat 的第一个字符索引
auto kmp = [](string str, string pat) -> vector<int> {
    int n = str.size(), m = pat.size();
    vector<int> p_pi(m);
    for (int i=1; i < m; i++) {
        int j = p_pi[i-1];
        while (j > 0 && pat[j]!=pat[i])
            j = p_pi[j-1];
        if (pat[j] == pat[i])
            p_pi[i] = j + 1;
        else p_pi[i] = j;
    }

    vector<int> ans;
    int j = 0;
    for (int i=0; i<n; i++) {
        while (j > 0 && str[i] != pat[j])
            j = p_pi[j-1];
        if (str[i] == pat[j]) j++;
        if (j == m) ans.push_back(i-j+1), j = p_pi[j-1];
    }

    return ans;
};


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


auto rabinKarp = [](string text, string patten) -> vector<int> {
    vector<int> result;
    int n = text.size(), m = patten.size();
    int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    int base1 = 401, base2 = 701;
    int bm1 = 1, bm2 = 1;

    // 计算 base 的 m-1 次方
    for (int _=0; _<m-1; ++_){
        bm1 = (bm1 * base1) % mod1;
        bm2 = (bm2 * base2) % mod2;
    }
    // 计算第一个匹配字符串和模式串的 hash
    pair<long long, long long> t = {0, 0}, p = {0, 0};
    for (int i=0; i<m; ++i) {
        t.first = (t.first * base1 + text[i]) % mod1;
        t.second = (t.second * base2 + text[i]) % mod2;
        p.first = (p.first * base1 + patten[i]) % mod1;
        p.second = (p.second * base2 + patten[i]) % mod2;
    }
    if (t == p) result.push_back(0);
    for (int i=m; i<n; ++i) {
        t.first = ((t.first + mod1 - (text[i-m] * bm1)%mod1) * base1 + text[i]) % mod1;
        t.second = ((t.second + mod2 - (text[i-m] * bm2)%mod2) * base2 + text[i]) % mod2;
        if (t == p) result.push_back(i-m+1);
    }

    return result;
};

int main() {
    // vector<int> ans = zFunc("bacabaababbababa");
    // vector<int> ans = kmp("1021102","102");
    vector<int> ans = rabinKarp("10211021022102102","102");
    for (auto v:ans) cout << v << " ";
    cout << endl;
}