#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> swapNumbers(vector<int>& numbers) {
        // +/- 会越界
        numbers[0] ^= numbers[1];
        numbers[1] = numbers[0]^numbers[1];
        numbers[0] ^= numbers[1];
        return numbers;
    }
};