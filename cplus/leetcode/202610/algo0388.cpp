#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        input += '\n';  // 哨兵
        vector<int> pres = {0}; char tab = '\t', lf= '\n';
        
        int i = 0, start = 0, n = input.length(); 
        bool isFile = false; int depth = 0, ans = 0;
        while (i < n) {
            if (input[i] == '.') {
                isFile = true;
            } else if (input[i] == tab) {
                depth += 1;
            } else if (input[i] == lf){ // input == lf
                if (depth+1 == pres.size()) pres.emplace_back(pres.back() + i - start - depth);
                else pres[depth+1] = pres[depth] + i - start - depth;
                if (isFile) ans = max(ans, pres[depth+1] + depth);
                start = i + 1; depth = 0; isFile = false;
            }
            i ++; 
        }
        return ans;        
    }
};