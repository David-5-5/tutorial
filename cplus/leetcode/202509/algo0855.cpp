#include <bits/stdc++.h>
using namespace std;

struct Comp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        int da = a.second - a.first, db = b.second - b.first;
        return da/2 < db/2 || (da/2==db/2 && a.first>b.first);
    }
};

class ExamRoom {
private:
    int n = 0;
    set<int> seats;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> dis;

public:
    ExamRoom(int n) {
        this->n = n;
    }
    
    int seat() {
        if (seats.size() == 0) {
            seats.insert(0);        // 两个距离单独处理，就是这一点没有想清楚
            return 0;
        }

        auto left = *seats.begin(), right = n - 1 - *seats.rbegin();
        while (seats.size() >= 2) {
            auto p = dis.top();
            // 检查是否有效区间，两端有人，中间空座
            if (seats.count(p.first) && seats.count(p.second) && 
                *next(seats.find(p.first))==p.second) {
                int d = p.second - p.first;
                if (d/2 < right || d/2 <= left) {
                    break; // 最左或最右位置更优
                }
                dis.pop();
                // p.first + d/2 
                // 若中间空座为奇数，p.first + d/2 为中间座位，
                // 若中间空座为偶数，p.first + d/2 为中间靠右座位，符合编号较小的要求，
                dis.emplace(p.first, p.first + d/2);
                dis.emplace(p.first + d/2, p.second);
                seats.insert(p.first + d/2);
                return p.first + d/2;
            }
            dis.pop();    // p 为无效区间，延时删除

        }
        // 仅有一个人，或坐两边更优
        if (left < right) {
            seats.insert(n-1);
            dis.emplace(n-1-right, n-1);
            return n-1;
        } else {
            seats.insert(0);
            dis.emplace(0, left);
            return 0;
        }

    }
    
    void leave(int p) {
        if (p != *seats.begin() && p != *seats.rbegin()) {
            auto it = seats.find(p);
            dis.emplace(*prev(it), *next(it));
        }
        seats.erase(p);
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */