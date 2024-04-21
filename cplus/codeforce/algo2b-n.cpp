#include <bits/stdc++.h>
#define int long long
using namespace std;

int read()
{
	char ch = getchar();
	int f = 1, x = 0;
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return f * x;
}

const int maxn = 1001;

int n, a[maxn][maxn], zx, zy;
bool zero;
char ans[maxn << 1];

struct pr
{
	int two, five;
	int dt, df;
} f[maxn][maxn];

pr calc(int x)
{
	pr ret;
	ret.five = ret.two = 0;

	if (x == 0)
	{
		return ret; // 0要特判
	}

	while (x % 2 == 0)
	{
		ret.two++;
		x >>= 1;
	}
	while (x % 5 == 0)
	{
		ret.five++;
		x /= 5;
	}
	return ret;
}

void readConsole()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = read();
			if (!a[i][j])
			{
				zero = 1;
				zx = i;
				zy = j;
			}
		}
	}
}

void generate(vector<int> &data)
{
	n = 1000;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int inx = (i * 1871 + j * 4001) % 1600;
			a[i][j] = data[inx];
			if (!a[i][j])
			{
				zero = 1;
				zx = i;
				zy = j;
			}
		}
	}
}

signed solution()
{
	for (int i = 2; i <= n; i++)
	{
		f[0][i].five = f[0][i].two = f[i][0].five = f[i][0].two = 0x7fffffff;
	}
	// cout << "边界 = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			pr tmp = calc(a[i][j]);

			if (f[i - 1][j].two < f[i][j - 1].two)
			{
				f[i][j].two = f[i - 1][j].two + tmp.two;
				f[i][j].dt = 'D'; // 可以同时维护路径
			}
			else
			{
				f[i][j].two = f[i][j - 1].two + tmp.two;
				f[i][j].dt = 'R';
			}
			if (f[i - 1][j].five < f[i][j - 1].five)
			{
				f[i][j].five = f[i - 1][j].five + tmp.five;
				f[i][j].df = 'D';
			}
			else
			{
				f[i][j].five = f[i][j - 1].five + tmp.five;
				f[i][j].df = 'R';
			}
		}
	}
	// cout << "状态转移 = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;

	if (zero && min(f[n][n].five, f[n][n].two) > 1)
	{ // 0要特判
		cout << 1 << endl;
		for (int i = 1; i < zy; i++)
		{
			cout << 'R';
		}
		for (int i = 1; i < n; i++)
		{ // 注意边界哦~
			cout << 'D';
		}
		for (int i = zy + 1; i <= n; i++)
		{
			cout << 'R';
		}
		return 0;
	}

	int t;
	if (f[n][n].five < f[n][n].two)
	{
		t = 1;
		cout << f[n][n].five << endl;
	}
	else
	{
		t = 2;
		cout << f[n][n].two << endl;
	}

	int x = n, y = n, cnt = 0;

	if (t == 1)
	{
		while (!(x == 1 && y == 1))
		{
			ans[++cnt] = f[x][y].df;
			if (f[x][y].df == 'D')
			{
				x--;
			}
			else
			{
				y--;
			}
		}
	}
	else
	{
		while (!(x == 1 && y == 1))
		{
			ans[++cnt] = f[x][y].dt;
			if (f[x][y].dt == 'D')
			{
				x--;
			}
			else
			{
				y--;
			}
		}
	}

	for (int i = cnt; i; i--)
	{
		cout << ans[i];
	}
	cout << endl;
}

clock_t start;

// for test
// signed main()
// {
// 	// Open the input file named "input.txt"
//     ifstream inputFile("algo2b.txt");
//     string line;
//     getline(inputFile, line);
//     inputFile.close();

//     vector<int> data;
//     size_t begin = 0;
//     size_t end = line.find(",");

//     start = clock();
//     while (end != string::npos)
//     {
//         data.push_back(stoi(line.substr(begin, end - begin)));
//         begin = end + 1;
//         end = line.find(",", begin);
//     }
//     data.push_back(stoi(line.substr(begin)));
// 	for (int i = 0; i < 100; i++)
// 	{
// 		generate(data);
// 		// cout << "generate = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;

// 		solution();
// 		cout << "time = " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
// 	}
// 	return 0;
// }

// for codeforce
signed main()
{
	readConsole();

	solution();
	return 0;
}

// https://www.cnblogs.com/huayucaiji/p/CF-2B.html