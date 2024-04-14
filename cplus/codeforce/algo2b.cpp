#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <random>

using namespace std;

// include 2,5 count

int solution(vector<vector<int>> m)
{
    int n = m.size();
    vector<map<int, int>> inc(2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (inc[0].find(m[i][j]) == inc[0].end())
            {
                int count = 0;
                int value = m[i][j];
                while (value % 2 == 0)
                {
                    value /= 2;
                    count++;
                }
                inc[0][m[i][j]] = count;
                count = 0;
                while (value % 5 == 0)
                {
                    value /= 5;
                    count++;
                }
                inc[1][m[i][j]] = count;
            }
        }
    }
    vector<vector<vector<int>>> dp(2);
    dp[0].resize(n);
    dp[1].resize(n);
    for (int i = 0; i < n; i++)
    {
        dp[0][i].resize(n);
        dp[1][i].resize(n);
    }

    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[k][i][j] = inc[k][m[i][j]];

                if (i > 0 && j > 0)
                {
                    dp[k][i][j] += min(dp[k][i - 1][j], dp[k][i][j - 1]);
                }
                else if (i > 0)
                    dp[k][i][j] += dp[k][i - 1][j];
                else if (j > 0)
                    dp[k][i][j] += dp[k][i][j - 1];
            }
        }
    }

    int minc = min(dp[0][n - 1][n - 1], dp[1][n - 1][n - 1]);
    int minx = 0;
    if (dp[1][n - 1][n - 1] < dp[0][n - 1][n - 1])
        minx = 1;

    cout << min(dp[0][n - 1][n - 1], dp[1][n - 1][n - 1]) << endl;

    vector<char> path(2 * n - 2);
    int inx = path.size();
    int x = n - 1, y = n - 1;
    while (inx-- > 0)
    {
        if (x > 0 && minc - inc[minx][m[x][y]] == dp[minx][x - 1][y])
        {
            path[inx] = 'D';
            minc = dp[minx][--x][y];
        }
        else
        {
            path[inx] = 'R';
            minc = dp[minx][x][--y];
        }
    }

    string str(path.begin(), path.end());

    cout << str << endl;
    return 0;
}

vector<vector<int>> readConsole()
{
    int n;
    cin >> n;
    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++)
    {
        matrix[i].resize(n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

vector<vector<int>> generate()
{
    random_device rd;
    int n = 100;
    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++)
    {
        matrix[i].resize(n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rd();
        }
    }
    return matrix;
}

int main()
{
    return solution(readConsole());
}