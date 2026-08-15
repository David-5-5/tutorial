#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {

        int n = arr.size(), l = -1, r = n + 1;

        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            if (mid == 0) mid ++;
            if (mid == n-1) mid --;

            if (arr[mid-1] < arr[mid] && arr[mid] > arr[mid+1]) return mid;
            else if (arr[mid-1] < arr[mid] && arr[mid] < arr[mid+1]) l = mid;
            else r = mid;
        }

        return 0;        
    }
};