#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int i = 0, n = data.size();
        while (i < n) {
            auto & x = data[i];
            if (x < 128) i += 1;
            else {
                int len = 1;
                if ((x & 248) == 240) len = 4;
                else if ((x & 240) == 224) len = 3;
                else if ((x & 224) == 192) len = 2;
                else return false;
                for (int j=1; j<len; j++) {
                    if (i+j==n || (data[i+j] & 192) != 128) return false;
                }
                i += len;
            }
        }
        return true;
    }
};