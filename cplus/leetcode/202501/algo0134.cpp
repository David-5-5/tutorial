#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if (accumulate(gas.begin(), gas.end(), 0) < accumulate(cost.begin(), cost.end(), 0)) return -1;
        
        int begin = 0, sum = 0;
        for (int i = 0; i<gas.size(); i++) {
            sum += gas[i] - cost[i];
            if (sum < 0) sum = 0, begin = i+1;
        }

        return begin;        
    }
};