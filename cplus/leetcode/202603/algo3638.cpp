#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int ans = 0, mx = weight[0], n = weight.size();
        
        int i = 1;
        while (i < n) {
            while (i<n && weight[i] >= mx) {
                mx = weight[i]; i++; 
            }
            if (i < n) {
                ans ++; if (i + 1 < n) mx = weight[++i];
            }
            i ++;
        }
        
        return ans;    
        
    }
};