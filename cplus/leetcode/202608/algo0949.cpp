#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        string ans = "";

        sort(arr.begin(), arr.end());
        do {
            if (arr[0]*10 + arr[1] < 24 && arr[2]*10 + arr[3] < 60) {
                string res = "00:00";
                res[0] = arr[0] + '0', res[1] = arr[1] + '0';
                res[3] = arr[2] + '0', res[4] = arr[3] + '0';
                ans = max(ans, res);
            }
        } while (next_permutation(arr.begin(), arr.end()) );

        return ans;
    }
};