#include <bits/stdc++.h>
using namespace std;

// gcd logtrick
int solution(vector<int> nums) {
    unordered_map<int, unsigned long long> cnt;
    deque<pair<int, unsigned long long>> arr_gcd;

    for (int i = 0; i<nums.size(); ++i) {
        for (int j=arr_gcd.size()-1; j>=0; --j) {
            if (arr_gcd[j].first == gcd(arr_gcd[j].first, nums[i])) break;
            arr_gcd[j].first = gcd(arr_gcd[j].first, nums[i]);
        }

        arr_gcd.emplace_back(nums[i], 1);

        auto it = arr_gcd.begin(); auto nxt = it + 1;
        while (it !=arr_gcd.end() && nxt != arr_gcd.end()) {
            
            while (it !=arr_gcd.end() && nxt != arr_gcd.end() && it->first == nxt->first) {
                nxt->second += it->second;
                it = next(it); nxt = next(nxt);
                arr_gcd.erase(prev(it));
            }
            if (it !=arr_gcd.end()) it = next(it);
            if (nxt != arr_gcd.end()) nxt = next(nxt);
        }
        for (auto &[k, v]:arr_gcd) cnt[k] += v;
    }

    int q; cin >> q;
    for (int i=0; i<q; ++i) {
        int k; cin >> k;
        cout << cnt[k] << endl;
    }
    return 0;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i){
        cin >> nums[i];
    }
    
    solution(nums);
    return 0;
}