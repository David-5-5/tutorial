#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  2.1 一维差分
class MyCalendarThree {
    map<int, int> diff;
public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        // 参考题解 同 731, 真是会者不难，难者不会!!!
        diff[startTime] ++;
        diff[endTime] --;
        
        int cnt = 0;
        for (auto& [_, c] : diff) {
            cnt += c;
        }

        return cnt;        
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */