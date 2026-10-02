#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        priority_queue<pair<int, int>> pq;

        int n = words.size();
        if (n == 1) return {0};
        for (int i=1; i<n; i++) {
            int lcp = 0;
            while (lcp < words[i-1].length() && lcp <words[i].length() &&
                 words[i-1][lcp] == words[i][lcp]) lcp ++;
            
            pq.emplace(lcp, i);
        }

        vector<int> ans(n); vector<pair<int, int>> pops;
        for (int i=0; i<n; i++) {
            int lcp = 0;
            if (i && i+1<n) {
                while (lcp < words[i-1].length() && lcp < words[i+1].length() &&
                    words[i-1][lcp] == words[i+1][lcp]) lcp ++;
            }

            while (!pq.empty() && (pq.top().second == i || pq.top().second == i+1)){
                pops.push_back(pq.top()); pq.pop();
            }
            ans[i] = max(lcp, !pq.empty()?pq.top().first:0);

            while (!pops.empty()) {
                pq.emplace(pops.back()); pops.pop_back();
            }
        }
        return ans;


    }
};

int main() {
    vector<string> words = {"beeac","aff"};
    Solution().longestCommonPrefix(words);
}