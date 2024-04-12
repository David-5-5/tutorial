#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Point
{
    int x;
    int y;
    int cnt2;
    int cnt5;
    string path;
};

string solution(vector<vector<int>> m)
{
    int n = m.size();

    // include 2,5 count
    map<int, int> inc2;
    map<int, int> inc5;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (inc2.find(m[i][j]) == inc2.end())
            {
                int count = 0;
                int value = m[i][j];
                while (value % 2 == 0)
                {
                    value /= 2;
                    count++;
                }
                inc2[m[i][j]] = count;
                count = 0;
                while (value % 5 == 0)
                {
                    value /= 5;
                    count++;
                }
                inc5[m[i][j]] = count;
            }
        }
    }

    map<int, vector<Point>> candiate;

    vector<Point> visiting;
    Point start = Point{0, 0, inc2[m[0][0]], inc5[m[0][0]], ""};

    visiting.push_back(start);
    int begin = 0;
    while (begin++ <= 2*n-2)
    {
        candiate.clear();
        for (int i = 0; i < visiting.size(); i++)
        {
            Point p = visiting[i];
            // to R
            if (p.x + 1 < n)
            {
                Point r = Point{p.x + 1, p.y, inc2[m[p.x + 1][p.y]] + p.cnt2, inc5[m[p.x + 1][p.y]] + p.cnt5, p.path + "D"};
                if (candiate.find(r.x * n + r.y) == candiate.end())
                {
                    vector<Point> can;
                    can.push_back(r);
                    candiate[r.x * n + r.y] = can;
                }
                else
                {
                    candiate[r.x * n + r.y].push_back(r);
                }
            }
            // to D
            if (p.y + 1 < n)
            {
                Point d = Point{p.x, p.y + 1, inc2[m[p.x][p.y + 1]] + p.cnt2, inc5[m[p.x][p.y + 1]] + p.cnt5, p.path + "R"};
                if (candiate.find(d.x * n + d.y) == candiate.end())
                {
                    vector<Point> can;
                    can.push_back(d);
                    candiate[d.x * n + d.y] = can;
                }
                else
                {
                    candiate[d.x * n + d.y].push_back(d);
                }
            }
        }
        visiting.clear();

        if (begin == 2*n - 2)
            break; 
        for (const auto &[_, v] : candiate)
        {
            if (v.size() == 1)
            {
                visiting.push_back(v[0]);
            }
            else
            {
                // delete the point of which cnt2, cnt5 both small than others
                set<int> todel;
                for (int i = 1; i < v.size(); i++)
                {
                    for (int j = 0; j < i; j++)
                    {
                        // 2, 5, i > j, both >= , at lease one >
                        if (v[j].cnt2 <= v[i].cnt2 && v[j].cnt5 <= v[i].cnt5 && v[j].cnt2 + v[j].cnt5 < v[i].cnt2 + v[i].cnt5)
                            todel.insert(i);
                        // 2, 5, j > i, both >= , at lease one >
                        if (v[i].cnt2 <= v[j].cnt2 && v[i].cnt5 <= v[j].cnt5 && v[i].cnt2 + v[i].cnt5 < v[j].cnt2 + v[j].cnt5)
                            todel.insert(j);
                        // both equals, reserve one
                        if (v[j].cnt2 == v[i].cnt2 && v[j].cnt5 == v[i].cnt5)
                            todel.insert(j);
                    }
                }
                for (int i = 0; i < v.size(); i++)
                {
                    if (todel.find(i) == todel.end())
                    {
                        visiting.push_back(v[i]);
                    }
                }
            }
        }
    }

    auto point = candiate[n * n - 1][0];
    int inx = 0;
    int cnt = min(point.cnt2, point.cnt5);
    for (int i = 1; i < candiate[n * n - 1].size(); i++)
    {
        if (cnt > min(candiate[n * n - 1][i].cnt2, candiate[n * n - 1][i].cnt5))
        {
            cnt = min(candiate[n * n - 1][i].cnt2, candiate[n * n - 1][i].cnt5);
            inx = i;
        }
    }
    cout << cnt << endl;
    return candiate[n * n - 1][inx].path;
}

int main()
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

    cout << solution(matrix) << endl;
}