#include <bits/stdc++.h>
using namespace std;
    
string input;
const int maxl = 50000;
int m;
int costs[maxl][2];

void solution(){
    int l = 0, r = 0, inx = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> lpq;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> rpq;
    vector<char> ans(input.length(), ' ');
    int cost = 0;
    for(int i=0; i<input.length(); i++) {
        if(input[i] == '?') {
            if (i + 1 == input.length()) {
                ans[i] = ')';
                cost += costs[inx][1];
                r++;
                continue;
            }
            if (costs[inx][0] < costs[inx][1]) {
                ans[i] = '(';
                if (l>r) lpq.push({costs[inx][1]-costs[inx][0], i});
                cost += costs[inx][0];
                l++;
            } else {
                if (l > r || (!rpq.empty() && rpq.top().first < costs[inx][0] - costs[inx][1])) {
                    if (l<=r) {
                        ans[rpq.top().second] = '(';
                        cost += rpq.top().first;
                        l++; r--;
                        rpq.pop();
                        while (!lpq.empty()) {
                            lpq.pop();
                        }
                    }
                    ans[i] = ')';
                    cost += costs[inx][1];
                    rpq.push({costs[inx][0] - costs[inx][1], i});
                    r++;
                } else {
                    ans[i] = '(';
                    cost += costs[inx][0];
                    // lpq.push({cost[inx][1]-cost[inx][0], i})
                    l++;
                }
            }
            inx ++;
        } else {
            ans[i] = input[i];
            if (input[i] == '(') l++; else r++;
        }
    }

    while (l > r && (l-r) % 2 == 0 && !lpq.empty()) {
        ans[lpq.top().second] = ')';
        cost += lpq.top().first;
        l--;
        r++;
        lpq.pop();
    }
    while (l < r && (r-l) % 2 == 0 && !rpq.empty()) {
        ans[rpq.top().second] = '(';
        cost += rpq.top().first;
        l++; r--;
        rpq.pop();
    }
    
    if (l != r) {
        cout << -1 << endl;
    } else {
        cout << cost << endl;
        for (int i=0; i<ans.size(); i++)
            cout << ans[i];
        cout << endl;
    }
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