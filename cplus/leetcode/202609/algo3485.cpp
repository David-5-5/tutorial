#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        // 排序后有个极其美妙的性质，就是 a[i] 和 a[i+k-1] 之间的lcp就是这 k 个 LCP
        // 更奇妙的性质，就算删除 mx 对应的 j \in i .. i+k-1 的值，也不需要比较
        //  a[i] 和 a[i+k] 或 a[i-1] 和 a[i+k-1] 之间的 LCP
        //  因此 a[i] 和 a[i+k] <= a[i+1] 和 a[i+k]
        int n = words.size();
        int idx[n]; vector<int> ans(n);
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return words[i] < words[j];
        });        

        int mx = 0, mx2 = 0, mx_l = -1;
        sort(words.begin(), words.end());

        for (int i=0; i<n-k+1; i++) {
            auto lcp = 0, j = i + k -1;
            while (lcp<words[i].length() && lcp<words[j].length() &&
                words[i][lcp] == words[j][lcp]) lcp ++;
            if (lcp > mx) {
                mx2 = mx;  mx = lcp, mx_l = i;
            } else if (lcp > mx2) {
                mx2 = lcp; 
            }
        }

        for (int i=0; i<n; i++) {
            if (i<mx_l || i > mx_l+k-1) ans[idx[i]] = mx;
            else ans[idx[i]] = mx2;
        }

        return ans;   
    }
};