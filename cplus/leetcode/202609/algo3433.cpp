#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> ans(numberOfUsers);

        sort(events.begin(), events.end(), [](const vector<string> a, const vector<string> b){
            if (stoi(a[1]) == stoi(b[1])) return a[0] > b[0];
            return stoi(a[1]) < stoi(b[1]);
        });

        unordered_map<int, int> offline;
        for (auto e: events) {
            auto type = e[0], id = e[2]; int ts = stoi(e[1]);
            if (type == "OFFLINE") {
                offline[stoi(id)] = ts + 60;
            } else {
                if (id == "ALL") {
                    for (int i = 0; i<numberOfUsers; i++) ans[i] ++;
                } else if (id == "HERE") {
                    for (int i = 0; i<numberOfUsers; i++) if (!offline.count(i) || offline[i]<=ts) ans[i] ++;
                } else {
                    istringstream iss(id);
                    string token;
                    while (iss >> token) {
                        ans[stoi(token.substr(2))] ++;
                    }
                }
            }
        }
        
        return ans;
    }
};