#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double angleClock(int hour, int minutes) {
        float angle = abs((hour % 12) * 5 + 5.0 * minutes / 60 - minutes);
        return  min(angle, 60-angle) * 6;
    }
};