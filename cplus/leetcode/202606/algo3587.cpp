#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        vector<int> odd, even;
        int n = nums.size();

        for (int i=0; i<n; i++) {
            if (nums[i] % 2) odd.push_back(i);
            else even.push_back(i);
        }

        if (abs((int)(odd.size() - even.size())) > 1) return -1;

        auto arrange = [&](const vector<vector<int>>& arrs) -> int {
            long long  res = 0;
            for (int i=0; i<n; i++) {
                int j = i % 2, k = i / 2;
                res += abs(arrs[j][k] - i);
            }
            return res / 2;
        };

        if (odd.size() == even.size()) return min(arrange({odd, even}), arrange({even, odd}));
        else if (odd.size() > even.size()) return arrange({odd, even});
        else return arrange({even, odd});        
    } 

    int minSwaps2(vector<int>& nums) {
        vector<int> odd, even;
        int n = nums.size();

        for (int i=0; i<n; i++) {
            if (nums[i] % 2) odd.push_back(i);
            else even.push_back(i);
        }

        if (abs((int)(odd.size() - even.size())) > 1) return -1;

        auto arrange = [&](vector<int>& arr0, vector<int>& arr1) -> int {
            long long  res = 0;
            for (int i=0; i<n; i++) {
                int j = i % 2, k = i / 2;
                if (j == 0)
                    res += abs(arr0[k] - i);
                else res += abs(arr1[k] - i);
            }
            return res / 2;
        };

        if (odd.size() == even.size()) return min(arrange(odd, even), arrange(even, odd));
        else if (odd.size() > even.size()) return arrange(odd, even);
        else return arrange(even, odd);   

    }

  
};