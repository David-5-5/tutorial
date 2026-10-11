#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfRounds(string loginTime, string logoutTime) {
        // 才开始复杂了
        int login = stoi(loginTime.substr(0, 2)) * 60 + stoi(loginTime.substr(3));
        int logout = stoi(logoutTime.substr(0, 2)) * 60 + stoi(logoutTime.substr(3));
        auto duration = logout - login;
        if (duration < 0) duration += 1440;

        duration -=  logout % 15 + (15-login % 15) % 15;
        return duration < 0?0:duration/15;
    }
};