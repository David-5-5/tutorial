#include <bits/stdc++.h>
using namespace std;

// 类似于 154
class Solution {
public:
    int search(vector<int>& arr, int target) {
        // Find max compare 154 旋转数组
        int l = 0, r = arr.size(), n = arr.size();
        while (l+1 < r) {
            auto m = (l + r) / 2;
            if (arr[m] == arr[l]) l ++;
            else if (arr[m] < arr[l]) r = m;
            else l = m;
        }

        if (l == n-1) { // 2 2 1 2 2 2  l = 5 -> l = 1
            while (arr[l] == arr[(l + 1)%n]) l = (l + 1)%n;
        }

        if (target == arr[0]) return 0;
        else if (target > arr[0]) {
            auto it = lower_bound(arr.begin(), arr.begin() + l + 1, target);
            if (*it == target) return it - arr.begin();
            else return -1;
        } else {
            auto it = lower_bound(arr.begin() + l + 1, arr.end(), target);
            if (it!=arr.end() && *it == target) return it - arr.begin();
            else return -1;
        }
        return -1;
    }

    int search(vector<int>& arr, int target) {
        // 暴力也能通过 
        for (int i=0; i<arr.size(); i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }    
};