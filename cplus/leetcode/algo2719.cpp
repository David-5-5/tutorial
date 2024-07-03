#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        const int MOD = 1e9 + 7;

        int n = num2.size();
        num1.insert(num1.begin(), n-num1.size(), '0');

        // Array out of bounds cause unpredictable result
        vector<vector<int>> memo(n, vector<int>(max_sum + 1, -1));

        function<int(int, int, bool, bool)> f = [&](int i, int ds, bool limit_low, bool limit_up){
            
            if (i == n){
                return (  ds >= min_sum)?1:0;
            }
            if (!limit_low && !limit_up && memo[i][ds] != -1)
                return memo[i][ds];
            
            int lo = (limit_low) ? stoi(num1.substr(i, 1)) : 0;
            int hi = (limit_up) ? stoi(num2.substr(i, 1)) : 9;

            int ans = 0;
            for (int k=lo; k<=hi; k++) {
                if (ds + k <= max_sum)
                    ans=(ans + f(i+1, ds+k, limit_low && k==lo, limit_up && k == hi)) % MOD;
            }
            if (!limit_low && !limit_up)
                memo[i][ds] = ans ;
            
            return ans;
        };
        return f(0, 0, true, true);
    }
};

int main()
{
    Solution solution;

    cout << solution.count("4179205230", "7748704426", 8, 46) << endl;
}