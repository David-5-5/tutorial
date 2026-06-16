#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size(), f = friendships.size();
        // 遍历语言 
        vector<bool> match(f);

        for (auto& lan:languages) sort(lan.begin(), lan.end());

        for (int i=0; i<f; i++) {
            auto m1 = friendships[i][0] - 1, m2 = friendships[i][1] - 1;
            bool mat = false; int l1 = 0, l2 = 0;
            auto & lan1 = languages[m1], & lan2 = languages[m2];
            while (!mat && l1 < lan1.size() && l2 < lan2.size()) {
                if (lan1[l1] == lan2[l2]) mat = true;
                else if (lan1[l1] > lan2[l2]) l2 ++ ;
                else l1 ++;
            }
            match[i] = mat;
        }

        int ans = m;
        for (int i=1; i<=n; i++) {
            set<int> teach;
            for (int j=0; j<f; j++) {
                if (match[j]) continue;
                auto m1 = friendships[j][0]-1, m2 = friendships[j][1]-1;

                auto it1 = ranges::lower_bound(languages[m1], i);
                if (it1 == languages[m1].end() || *it1 != i) teach.insert(m1);
                
                auto it2 = ranges::lower_bound(languages[m2], i);
                if (it2 == languages[m2].end() || *it2 != i) teach.insert(m2);
            }
            ans = min(ans, (int)teach.size());
        }
        return ans;        
    }
};
