#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string maskPII(string s) {
        string ans;

        bool mail = false;
        if ((s[0] >='a' && s[0] <= 'z') || (s[0] >='A' && s[0] <= 'Z')) mail = true;

        if (mail) {
            ans += (s[0] >='A' && s[0] <= 'Z')?s[0]-'A'+'a':s[0];
            ans += "*****"; 
            bool domain = false;
            for (int i=1; i<s.length(); i++) { 
                if (!domain) {
                    if (s[i] == '@') {
                        ans += (s[i-1] >='A' && s[i-1] <= 'Z')?s[i-1]-'A'+'a':s[i-1];
                        ans += s[i];
                        domain = true;
                    }
                } else ans += (s[i] >='A' && s[i] <= 'Z')?s[i]-'A'+'a':s[i];
            }                
        } else {
            for (auto & ch : s) {
                if (ch >= '0' && ch <= '9') ans += ch;
            }
            ans = (ans.length()>10?"+" + string(ans.length()-10, '*')+"-":"") + "***-***-" + ans.substr(ans.length()-4);
        }
        
        return ans;
    }
};