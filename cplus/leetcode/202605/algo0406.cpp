#include <bits/stdc++.h>
using namespace std;

// 六、构造题
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 自行解答
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int> b) {
            if (a[1] == b[1]) return a[0] < b[0];
            return a[1] < b[1];
        });

        vector<vector<int>> ans;

        for (auto p: people) {
            int rem = p[1];
            auto it = ans.begin();

            while (it != ans.end() && (rem || (*it)[0] < p[0])) {
                if ((*it)[0] >= p[0]) rem--;
                it ++;
            }
            it = ans.insert(it, p); it ++;
        }

        return ans;   
    }
};

int main() {
    vector<vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    Solution().reconstructQueue(people);
}