#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        // 自行解答
        int targetArrival = times[targetFriend][0], thres = 0;
        sort(times.begin(), times.end());
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> leavings;
        priority_queue<int, vector<int>, greater<>> pq_avail;

        for (auto t: times) {
            int arr = t[0], leav = t[1];
            while (leavings.size() && leavings.top().first<=arr) {
                int pos = leavings.top().second;
                if (pos < thres) pq_avail.push(pos);
                leavings.pop();         // 出队列
            }

            int new_pos;
            if (pq_avail.empty()) new_pos = thres ++;
            else new_pos = pq_avail.top(), pq_avail.pop();

            if (arr == targetArrival) {
                return new_pos;
            } else {
                leavings.emplace(leav, new_pos);
            }

        }
        return 0;  
    }
};

int main() {
    vector<vector<int>> times = {{99999,100000}, {1,2}};
    cout<< Solution().smallestChair(times, 0) << endl;
}