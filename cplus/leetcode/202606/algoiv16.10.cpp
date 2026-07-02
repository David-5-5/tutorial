#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxAliveYear(vector<int>& birth, vector<int>& death) {
        vector<int> diff(120);

        int n = birth.size();
        for (int i=0; i<n; i++) {
            diff[birth[i]-1900] ++;
            diff[death[i]-1900+1] --;
        }

        int year=1900, mx = 0, sum = 0;
        for (int i=0; i<diff.size(); i++) {
            sum += diff[i];
            if (sum > mx) {
                year = 1900 + i; mx = sum;
            }
        }

        return year;
    }
};