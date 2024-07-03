#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s)
    {
        string sf = to_string(finish);
        string ss = to_string(start);
        ss.insert(ss.begin(), sf.size() - ss.size(), '0');
        int diff = sf.size() - s.size();

        vector<long long> memo(sf.size(), -1);

        function<long long(int, bool, bool)> f = [&](int i, bool limit_low, bool limit_up)
        {
            if (i == sf.size())
            {
                return (long long)1;
            }

            if (!limit_low && !limit_up && memo[i] != -1)
                return memo[i];


            int lo = (limit_low) ? stoi(ss.substr(i, 1)) : 0;
            int hi = (limit_up) ? stoi(sf.substr(i, 1)) : 9;

            long long ans = 0;

            if (i < diff)
            {
                for (int k = lo; k <= hi && k <= limit; k++)
                    ans += f(i + 1, limit_low && k == lo, limit_up && k == hi);
            }
            else
            {
                int x = stoi(s.substr(i - diff, 1));
                if (x >= lo && x <= hi && x <= limit)
                    ans += f(i + 1, limit_low && x == lo, limit_up && x == hi);
            }
            if (!limit_low && !limit_up) {
                memo[i] = ans;
            }
            return ans;
        };

        return f(0, true, true);
    }
};

int main()
{
    Solution solution;

    cout << solution.numberOfPowerfulInt(15, 215, 6, "10") << endl;
}