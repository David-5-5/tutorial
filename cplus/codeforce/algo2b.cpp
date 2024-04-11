#include <iostream>
#include <vector>
using namespace std;

string solution(vector<vector<int>> m)
{
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