#include <vector>
#include <functional>
#include <iostream>

using namespace std;

class Solution
{
private:
    vector<vector<int>> dp;
    vector<int> presum;

public:
    int dfs(const vector<int> &stoneValue, int l, int r)
    {
        if (dp[l][r])
            return dp[l][r];

        if (l == r)
            return 0;

        if (l + 1 == r)
        {
            return min(stoneValue[l], stoneValue[r]);
        }

        int sum = presum[r + 1] - presum[l];
        int suml = 0;

        for (int k = l; k < r; k++)
        {
            suml += stoneValue[k];
            int sumr = sum - suml;
            if (suml > sumr)
            {
                dp[l][r] = max(dp[l][r], dfs(stoneValue, k + 1, r) + sumr);
            }
            else if (suml < sumr)
            {
                dp[l][r] = max(dp[l][r], dfs(stoneValue, l, k) + suml);
            }
            else
            {
                dp[l][r] = max(dp[l][r], dfs(stoneValue, k + 1, r) + sumr);
                dp[l][r] = max(dp[l][r], dfs(stoneValue, l, k) + suml);
            }
        }
        return dp[l][r];
    }

    int stoneGameV(vector<int> &stoneValue)
    {
        int n = stoneValue.size();

        dp.assign(n, vector<int>(n));
        presum.resize(n + 1);

        for (int i = 0; i < n; i++)
        {
            presum[i + 1] = presum[i] + stoneValue[i];
        }

        return dfs(stoneValue, 0, n - 1);
    };
};

class Solution2
{
private:
    vector<vector<int>> dp;
    vector<int> presum;

public:
    int stoneGameV(vector<int> &stoneValue)
    {
        int n = stoneValue.size();

        dp.assign(n, vector<int>(n));
        presum.resize(n + 1);

        for (int i = 0; i < n; i++)
        {
            presum[i + 1] = presum[i] + stoneValue[i];
        }
        function<int(int, int)> dfs = [&](int l, int r)
        {
            if (dp[l][r])
                return dp[l][r];

            if (l == r)
                return 0;

            if (l + 1 == r)
            {
                return min(stoneValue[l], stoneValue[r]);
            }

            int sum = presum[r + 1] - presum[l];
            int suml = 0;

            for (int k = l; k < r; k++)
            {
                suml += stoneValue[k];
                int sumr = sum - suml;
                if (suml > sumr)
                {
                    dp[l][r] = max(dp[l][r], dfs(k + 1, r) + sumr);
                }
                else if (suml < sumr)
                {
                    dp[l][r] = max(dp[l][r], dfs(l, k) + suml);
                }
                else
                {
                    dp[l][r] = max(dp[l][r], dfs(k + 1, r) + sumr);
                    dp[l][r] = max(dp[l][r], dfs(l, k) + suml);
                }
            }
            return dp[l][r];
        };
        return dfs(0, n - 1);
    };
};

class Solution3
{
private:
    vector<vector<int>> dp;
    vector<int> presum;

public:
    int stoneGameV(vector<int> &stoneValue)
    {
        int n = stoneValue.size();

        dp.assign(n, vector<int>(n));
        presum.resize(n + 1);

        for (int i = 0; i < n; i++)
        {
            presum[i + 1] = presum[i] + stoneValue[i];
        }
        function<int(int, int)> dfs = [&](int l, int r)
        {
            if (dp[l][r])
                return dp[l][r];

            if (l == r)
                return 0;

            if (l + 1 == r)
            {
                return min(stoneValue[l], stoneValue[r]);
            }

            for (int k = l; k < r; k++)
            {
                if (presum[k+1]-presum[l] > presum[r+1] - presum[k+1])
                {
                    dp[l][r] = max(dp[l][r], dfs(k + 1, r) + presum[r+1] - presum[k+1]);
                }
                else if (presum[k+1]-presum[l] < presum[r+1] - presum[k+1])
                {
                    dp[l][r] = max(dp[l][r], dfs(l, k) + presum[k+1]-presum[l]);
                }
                else
                {
                    dp[l][r] = max(dp[l][r], dfs(l, k) + presum[k+1]-presum[l]);
                    dp[l][r] = max(dp[l][r], dfs(k + 1, r) + presum[r+1] - presum[k+1]);
                }
            }
            return dp[l][r];
        };
        return dfs(0, n - 1);
    };
};

int main()
{
    Solution3 solution;

    vector<int> input{6, 2, 3, 4, 5, 5};
    cout << solution.stoneGameV(input) << endl;

    return 0;
}