#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alphabetBoardPath(string target) {
        int x = 0, y = 0; string path;

        for (auto & t: target) {
            auto tx = (t - 'a') / 5, ty = (t - 'a') % 5;
            if (t == 'z') {
                if (y > ty) while (y!=ty) {path += "L", y--;}
                else while (y!=ty) {path += "R", y++;}
                if (x > tx) while (x!=tx) {path += "U", x--;}
                else while (x!=tx) {path += "D", x++;}
            } else {
                if (x > tx) while (x!=tx) {path += "U", x--;}
                else while (x!=tx) {path += "D", x++;}
                if (y > ty) while (y!=ty) {path += "L", y--;}
                else while (y!=ty) {path += "R", y++;}
            }
            path += "!";
        }

        return path;

    }
};