#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int cnt = 0, suf0 = 0, n = arr.size();
        for (auto v: arr) if (v) cnt += 1;
        if (cnt == 0) return {0, 2};
        if (cnt % 3) return {-1, -1};
        
        for (int i=n-1; i; i--) {
            if (arr[i]) break;
            suf0 ++;
        }

        int s = -1, t = -1, one = 0;
        for (int i=0; i<n; i++) {
            if (arr[i]) {
                one ++;
                if (one == cnt / 3) s = i + suf0;
                else if (one == 2 * cnt / 3) t = i + suf0;
            }
        }

        if (s == -1 || t == -1) return {-1, -1};
        one = cnt / 3;

        int i = s, j = t;
        for (int k=n-1; k>t; k--) {
            if (i < 0 || j <= s) break;
            if (arr[k] == arr[i--] && arr[k] == arr[j--]) {
                if (arr[k]) one --;
            } else return {-1, -1};
        }
        if (one == 0) return {s, t + 1};
        else return {-1, -1};   
    }
};

int main() {
    vector<int> arr = {0,1,1,0,1};
    Solution().threeEqualParts(arr);
}