#include <bits/stdc++.h>
using namespace std;
    
string input;
const int maxl = 50000;
int m;
int costs[maxl][2];

void solution_wrong_21(){
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


void solution() {
    // 2025.1
    // 参考题解，贪心 关键思路，首先将 ? 都先改为 ), 然后使用反悔贪心，选择cost最小的(costl-costr的值最小) ? 进行反悔
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    int lb = 0, rb = 0, inx = 0;
    long long cost = 0;// 统计左右括号数量, inx 为 ? 索引
    vector<char> ans(input.length(), ' ');
    for(int i=0; i<input.length(); i++) {
        // 默认将 ? 都转换为 ), 设置到 ans 中
        if (input[i] == '?') {
            ans[i] = ')';
            pq.push({costs[inx][0]-costs[inx][1], i}); // 元素 {反悔的价值变更，索引}
            cost += costs[inx++][1]; // 右括号价值
        }
        else ans[i] = input[i];

        if (ans[i] == '(') lb ++;
        else rb ++;

        if (rb > lb) {
            if (pq.empty()) break;      // 无法反悔，退出循环，不匹配
            ans[pq.top().second] = '('; // 进行反悔
            cost += pq.top().first;
            pq.pop(), lb++, rb--;
        }
    }

    // 输出结果
    if (lb != rb) {
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