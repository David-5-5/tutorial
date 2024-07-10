#include <bits/stdc++.h>
using namespace std;
// refer to https://leetcode.cn/problems/minimum-reverse-operations/solutions/2204092/liang-chong-zuo-fa-ping-heng-shu-bing-ch-vr0z/
class Solution
{
public:
    vector<int> minReverseOperations(int n, int p, vector<int> &banned, int k)
    {
        unordered_set ban(banned.begin(), banned.end());
        set<int> sets[2];
        vector<int> ans(n, -1);

        for (int i = 0; i < n; i++)
        {
            if (i != p && !ban.count(i))
                sets[i % 2].insert(i);
        }
        sets[0].insert(n);
        sets[1].insert(n);

        vector<int> q = {p};

        for (int step = 0; !q.empty(); step++)
        {
            vector<int> nq;
            for (int i : q)
            {
                ans[i] = step;
                int mn = max(i - k + 1, k - i - 1);
                int mx = min(i + k - 1, 2 * n - k - i - 1);
                auto &s = sets[mn % 2];
                for (auto it = s.lower_bound(mn); *it <= mx; it = s.erase(it))
                    nq.push_back(*it);
            }
            q = move(nq);
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    int n = 4, p = 0, k = 4;
    vector<int> banned = {1, 2};
    vector<int> ans = solution.minReverseOperations(n, p, banned, k);

    cout << "[";
    for (int i : ans)
        cout << i << ", ";
    cout << "]" << endl;
}