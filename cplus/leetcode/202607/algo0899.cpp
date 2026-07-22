#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        // 自行解答，观察规律
        if (k > 1) {
            sort(s.begin(), s.end()); return s;
        }

        vector<int> idx[26];
        for (int i=0; i<s.length(); i++) idx[s[i]-'a'].push_back(i);
        string ans = s;
        for (int i=0; i<26; i++) {
            if (idx[i].size()) {
                for (int pos : idx[i]) {
                    auto cur = s.substr(pos) + s.substr(0, pos);
                    ans = min(ans, cur);
                }
                break;
            }
        }
        
        return ans;
    }

    string orderlyQueue2(string s, int k) {
        if (k > 1) {
            sort(s.begin(), s.end()); return s;
        }

        // oi-wiki 字符串 循环同构最小字典序 朴素算法 O(N^2)
        int l = 0, i = 0, j = 1, n = s.length();
        while (l < n && i < n && j < n) {
            if (s[(i+l) % n] == s[(j+l) % n]) l++;
            else {
                s[(i+l) % n] > s[(j+l) % n]?i++:j=j++;
                if (i == j) i++;
                l = 0;
            }
        }
        i = min(i, j);
        return s.substr(i) + s.substr(0, i);
    }

    string orderlyQueue3(string s, int k) {
        // 进阶
        if (k > 1) {
            sort(s.begin(), s.end()); return s;
        }

        // oi-wiki 字符串 循环同构最小字典序  最小表示法 O(N)
        int l = 0, i = 0, j = 1, n = s.length();
        while (l < n && i < n && j < n) {
            if (s[(i+l) % n] == s[(j+l) % n]) l++;
            else {
                s[(i+l) % n] > s[(j+l) % n]?i=i+l+1:j=j+l+1;
                if (i == j) i++;
                l = 0;
            }
        }
        i = min(i, j);
        return s.substr(i) + s.substr(0, i);
    }    
};