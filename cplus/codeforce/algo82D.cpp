#include <bits/stdc++.h>
using namespace std;

// 同leetcode 3469
int minCost(vector<int>& nums) {
    int n = nums.size();

    vector<vector<int>> dp(n+1, vector<int>(n));

    dp[n] = nums;
    for (int i=0; i<n; i++) 
        dp[n-1][i] = max(nums[i], nums[n-1]);

    for (int i=n-3 + n%2; i>0; i-=2) {
        int b = nums[i], c = nums[i+1];
        for (int j=0; j<i; j++) {
            int a = nums[j];
            dp[i][j] = min({dp[i+2][j] + max(b,c), 
                            dp[i+2][i] + max(a,c),
                            dp[i+2][i+1] + max(a, b)});
        }

    }
    int mn = dp[1][0];
    // print the result
    cout << mn << endl;
    int j = 0;
    for (int i=1; i<=n; i+=2) {
        if (i == n) {
            cout << j + 1 << " " << endl;
            break;
        }
        if (i == n - 1) {
            cout << j + 1 << " " << n << endl;
            break;
        }

        int a = nums[j], b = nums[i], c=nums[i+1];

        if (dp[i+2][i] + max(a,c) == dp[i][j]) {
            cout << j + 1 << " " << i + 2 << endl;
            j = i;
        } else if (dp[i+2][i+1] + max(a,b) == dp[i][j]) {
            cout << j + 1 << " " << i + 1 << endl;
            j = i + 1;
        } else {
            cout << i + 1 << " " << i + 2 << endl;
        }
    }

    return 0;
};

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i=0; i<n; i++) cin >> nums[i];

    minCost(nums);

}