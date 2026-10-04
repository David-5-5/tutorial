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

    int minArrivalsToDiscard2(vector<int>& arrivals, int w, int m) {
        int n = arrivals.size(), ans = 0; vector<bool> discards(n);
        unordered_map<int, int> cnt;

        for (int i=0; i<n; i++) {
            if (i-w >= 0 && !discards[i-w]) cnt[arrivals[i-w]] --;

            if (cnt[arrivals[i]] < m) cnt[arrivals[i]] ++;
            else {discards[i] = true; ans ++;}
        }

        return ans;
    }    
};