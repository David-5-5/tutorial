#include <iostream>
#include <vector>
#include <map>

using namespace std;

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
            if (inc2.find(m[i][j])==inc2.end()) {
                int count = 0;
                int value = m[i][j];
                while (value % 2 == 0) {
                    value /= 2;
                    count ++;
                }
                inc2[m[i][j]] = count;
                count = 0;
                while (value % 5 == 0) {
                    value /= 5;
                    count ++;
                }
                inc5[m[i][j]] = count;
            }
        }
    }
    

    return "ok";
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