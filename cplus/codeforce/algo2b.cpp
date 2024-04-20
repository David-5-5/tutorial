#include <bits/stdc++.h>
#define int long long
using namespace std;

// include 2,5 count

int inc[2][1001][1001];
int dp[2][1001][1001];
int n, zx, zy;
// clock_t start;
bool zero;

int solution()
{
    for (int i = 2; i <= n; i++)
    {
        dp[0][0][i] = dp[1][0][i] = dp[0][i][0] = dp[1][i][0] = 0x7fffffff;
    }
    // cout << "边界 = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dp[0][i - 1][j] > dp[0][i][j - 1])
                dp[0][i][j] = dp[0][i][j - 1] + inc[0][i][j];
            else
                dp[0][i][j] = dp[0][i - 1][j] + inc[0][i][j];
            if (dp[1][i - 1][j] > dp[1][i][j - 1])
                dp[1][i][j] = dp[1][i][j - 1] + inc[1][i][j];
            else
                dp[1][i][j] = dp[1][i - 1][j] + inc[1][i][j];
        }
    }
    // cout << "状态转移 = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
	if(zero&&min(dp[1][n][n],dp[0][n][n])>1) {//0要特判
		cout<<1<<endl;
		for(int i=1;i<zy;i++) {
			cout<<'R';
		}
		for(int i=1;i<n;i++) {//注意边界哦~
			cout<<'D';
		}
		for(int i=zy+1;i<=n;i++) {
			cout<<'R';
		}
		return 0;
	}

    int minc = min(dp[0][n][n], dp[1][n][n]);
    int minx = 0;
    if (dp[1][n][n] < dp[0][n][n])
        minx = 1;

    cout << min(dp[0][n][n], dp[1][n][n]) << endl;

    vector<char> path(2 * n - 2);
    int inx = path.size();
    int x = n, y = n;
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

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int value;
            cin >> value;
            if (!value)
            {
                zero = 1;
                zx = i;
                zy = j;
            }
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
    n = 1200;

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

signed main()
{
    // start = clock();
    readConsole();
    // generate();
    // cout << "generate = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
    solution();
    // cout << "time = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
}