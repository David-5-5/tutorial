#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <random>

using namespace std;

// include 2,5 count

int inc[2][1000][1000];
int dp[2][1000][1000];
int n;

int solution()
{

    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[k][i][j] = inc[k][i][j];

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
        if (x > 0 && minc - inc[minx][x][y] == dp[minx][x - 1][y])
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

void readConsole()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int value;
            cin >> value;

            while (value % 2 == 0)
            {
                value /= 2;
                inc[0][i][j] += 1;
            }

            while (value % 5 == 0)
            {
                value /= 5;
                inc[1][i][j] += 1;
            }
        }
    }
}

void generate()
{
    random_device rd;
    n = 1000;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int value = rd();

            while (value % 2 == 0)
            {
                value /= 2;
                inc[0][i][j] += 1;
            }
            while (value % 5 == 0)
            {
                value /= 5;
                inc[1][i][j] += 1;
            }
        }
    }
}

int main()
{
    // clock_t start = clock();
    readConsole();
    // generate();
    solution();
    // cout << "time = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
}