#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.5 动态开点线段树
class MyCalendar {
private:
    map<int, int> mp; // key: start time, value: end time
public:
    MyCalendar() {
        
    }
    bool book(int startTime, int endTime) {
        // 自行解答 方法一 使用有序哈希表
        auto it = mp.lower_bound(startTime);
        if (it!=mp.begin() && prev(it)->second > startTime) return false;
        if (it!=mp.end() && endTime > it->first) return false;
        
        mp[startTime] = endTime;
        return true;
    }


};