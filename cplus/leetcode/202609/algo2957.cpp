#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int n = word.length(), ans = 0, i = 1;

        while (i<n) {
            if (abs(word[i]-word[i-1]) < 2) {ans ++; i += 2;}
            else i++;
        }
        return ans;
    }
};