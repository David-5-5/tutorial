#include <bits/stdc++.h>
using namespace std;

// 同 528
class Solution {
private:
    map<int, int> pro_inx;
    int sum = 0;
public:
    Solution(vector<int>& w) {
        int pre = 0;
        for (int i=0; i<w.size(); ++i){
            pro_inx[pre] = i; pre += w[i];
        }
        sum = pre;
    }
    
    int pickIndex() {
        int inx = rand() % sum;
        auto it = pro_inx.upper_bound(inx);
        --it;
        return it->second;
    }
};