#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.3 距离和
class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        // 自行解答 绝对值之和 数学公式推导 前缀和 
        // sum(nums[i] - nums[j])  0 <= j < n j!=i
        // = (nums[i] * (i) - (nums[0]...nums[i-1]) + nums[i+1] +.. + nums[n-1] - nums[i] * (n-1-i)
        // = pres[n] - pres[i] - pres[i+1] + nums[i] * (2 * i + 1 - n)
        // = pres[n] + nums[i] * (2 * i + 1 - n)
        // 
        int n = nums.size();
        vector<long> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];        

        vector<int> ans;
        for (int i=0; i<n; i++) {
            ans.push_back(pres[n] + nums[i] * (2*i+1-n)-pres[i]-pres[i+1]) ;
        }
        return ans;    
    }
};