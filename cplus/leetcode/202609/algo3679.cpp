#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {
        set<int> discards; int n = arrivals.size();
        unordered_map<int, int> cnt;

        for (int i=0; i<n; i++) {
            if (i-w >= 0 && !discards.count(i-w)) cnt[arrivals[i-w]] --;

            if (cnt[arrivals[i]] < m) cnt[arrivals[i]] ++;
            else discards.insert(i);
        }

        return discards.size(); 
    }
  
};