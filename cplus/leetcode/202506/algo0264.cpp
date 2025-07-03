#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.4 堆 - 第 K 小/大
class Solution {
public:
    int nthUglyNumber(int n) {
        int factors[] = {2, 3, 5};
        priority_queue<int, vector<int>, greater<>> pq;
        set<int> contains;
        contains.insert(1); pq.emplace(1);

        for (int _=0; _<n-1; ++_) {
            int mn = pq.top(); pq.pop();
            for (int i=0; i<3; ++i) {
                int val = mn * factors[i];
                if (!contains.count(val)) {
                    pq.emplace(val); contains.insert(val);
                }
            }
        }

        return pq.top();
    }
};