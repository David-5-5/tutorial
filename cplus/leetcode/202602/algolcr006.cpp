#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // 同 167，仅下标起始不同
        int n = numbers.size(); vector<int> ans = {0, n-1};
        while (true) {
            int & l = ans[0], & r = ans[1];
            if (numbers[l] + numbers[r] == target) return ans;
            else if ((numbers[l] + numbers[r] > target)) r--;
            else l ++;
        }   
    }
};