#include <bits/stdc++.h>
using namespace std;
    
string input;
const int maxl = 50000;
int m;
int costs[maxl][2];

void solution(){
    cout << input << endl;
}

int main()
{

    cin >> input;
    m = count(input.begin(),input.end(), '?');
    for (int i = 0; i < m; i++)
    {
        cin >> costs[i][0] >> costs[i][1];
    }
    
    solution();
    return 0;
}