#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 脑筋急转弯
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        // 计算最后一个乘客到站时间，由于时间不能相同，然后往前倒推 passengers 的空余时间
        // 如果没有空余时间，则为 1, 题目条件 passengers[i] >= 2
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        
        int p_i = 0, last=0;

        for (int i=0; i<buses.size(); i++) {
            int cur = 0;
            while (cur < capacity && p_i < passengers.size() && passengers[p_i] <= buses[i])
                cur ++, p_i ++;
            if (cur == capacity) last = passengers[p_i-1];
            else last = buses[i];
        }

        for (int i=passengers.size()-1; i>=0; i--) {
            if (passengers[i] < last) break;
            else if (passengers[i] == last) last --;
        }

        return last;    
    }   
};