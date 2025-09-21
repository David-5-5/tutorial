#include <bits/stdc++.h>
using namespace std;

// 其他递归/分治
class Solution {
public:
    string decodeAtIndex(string s, int k) {
        stack<tuple<int, string, int>> st;
        long long len = 0; int prev = 0, i = 0, n = s.length();
        while (len < k) {
            while (i < n && s[i]<'1' || s[i]>'9') i++;
            st.emplace(len, s.substr(prev, i-prev), i==n?1:s[i] - '0');
            len = (len + i - prev) * (i==n?1:s[i] - '0');
            prev = ++i;
        }

        auto find = [&](this auto&& find, int l) -> string {
            len /= get<2>(st.top());
            l = l % len;
            if (l >= get<0>(st.top())){
                // cout << get<1>(st.top()).substr(2,1) << endl;
                return get<1>(st.top()).substr(l-get<0>(st.top()),1);
            } else {
                len -= get<1>(st.top()).length(); st.pop();
                return find(l);
            }
        };

        return find(k-1);

    }
};

int main() {
    cout << Solution().decodeAtIndex("aw4eguc6cs", 41) << endl; 
}