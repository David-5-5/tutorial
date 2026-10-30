#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countSubstrings(string s) {
        long long ans = 0; int n = s.length();
        
        vector<int> last(10, -1);
        for (int i=0; i<n; i++) {
            if (s[i] == '2' || s[i] == '1') ans += i + 1;
            last[s[i]-'0'] = i;
        }

        for (int div=3; div<10; div++) {
            vector<int> p_rem(div);
            for (int i=0; i<n && i<=last[div]; i++) {
                vector<int> c_rem(div);
                auto num = s[i] - '0';

                c_rem[num % div] ++;
                for (int rem=0; rem<div; rem++) {
                    if (p_rem[rem] == 0) continue;
                    c_rem[(rem*10+num) % div] += p_rem[rem];
                }
                if (div == num) ans += c_rem[0];
                p_rem = c_rem;
            }
        }
        return ans; 
    }
};

int main() {
    cout << Solution().countSubstrings("12936") << endl;
}