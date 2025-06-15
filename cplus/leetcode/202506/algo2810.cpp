#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.3 队列 - 双端队列
class Solution {
public:
    string finalString(string s) {
        // 自行解答
        deque<char> que;
        int back = 1;

        for (auto& ch: s) {
            if (ch == 'i') back ^= 1;
            else if (back) que.push_back(ch);
            else que.push_front(ch);
        }

        string ans = "";
        if (back) 
            while (!que.empty())
                ans += que.front(), que.pop_front();
        else 
            while (!que.empty())
                ans += que.back(), que.pop_back();

        return ans;
    }   
};