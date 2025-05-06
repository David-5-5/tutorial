#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  2.1 一维差分
class MyCalendarTwo {
private:
    map<int, int> diff;
public:
    MyCalendarTwo() {
    }
    
    bool book(int startTime, int endTime) {
        // 参考题解 用差分数组结合区间统计
        diff[startTime] ++;
        diff[endTime] --;
        
        int cnt = 0;
        for (auto& [_, c] : diff) {
            cnt += c;
            if (cnt > 2) {
                diff[startTime] --;
                diff[endTime] ++;
                return false;
            }
        }

        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */