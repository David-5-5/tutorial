#include <bits/stdc++.h>
using namespace std;

// 后缀求和 ，未用到 abel 求和
long long solution(vector<int>& nums, int k) {
    vector<long long> suf_sum;
    int n = nums.size();
    long long sum = 0;
    for (int i=n-1; i; --i) {
        sum += nums[i];
        suf_sum.push_back(sum);
    }
    long long  ans = sum + nums[0];             // 必须包含全部元素的和
    sort(suf_sum.rbegin(), suf_sum.rend());     // 取最大的 k-1 个后缀和
    for (int i=0; i<k-1; ++i) {
        ans += suf_sum[i];
    }
    
    return ans;
};

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    
    cout << solution(nums, k);
    return 0;
}