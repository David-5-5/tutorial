#include <bits/stdc++.h>
using namespace std;


int special(vector<int>& arr) {
    int n = arr.size(), ans = 0;
    vector<int> cnt(n+1);
    for (auto a: arr) cnt[a] += 1;
    
    for (int l=0; l<n-1; ++l) {
        int sum = arr[l];
        for (int r=l+1; r<n; ++r) {
            sum += arr[r];
            if (sum > n) break;
            if (cnt[sum]) {
                ans += cnt[sum]; cnt[sum] = 0;
            }
        }
        
    }
    return ans;
};

int main() {
    int t;
    cin >> t;

    for (int i=0; i<t; ++i) {
        int n; cin >> n;
        vector<int> arr(n);
        for (int j=0; j<n; ++j) cin >> arr[j];
        cout << special(arr) << endl;
    }
}