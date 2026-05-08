#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.3 等价转换
class Solution {
public:
    bool isPossibleToRearrange(string s, string t, int k) {
        // 自行解答，效率不高
        int n = s.length(), len = n / k;
        multiset<string> segments;
        for (int i=0; i<n; i+=len) segments.insert(s.substr(i, len));

        for (int i=0; i<n; i+=len) {
            string seg = t.substr(i, len);
            auto it = segments.find(seg);
            if (it != segments.end()) segments.erase(it);
            else return false;
        }
        return true;  
    }
};