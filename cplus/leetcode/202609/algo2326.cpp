#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector ans(m, vector<int>(n, -1));

        const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        int d = 0, i = 0, j = 0;

        auto next = [&]() {
            auto i_ = i+dirs[d][0], j_ = j+dirs[d][1];
            if (i_<0 || i_==m || j_<0 || j_==n || ans[i_][j_] >= 0)
                d = (d + 1) % 4;
 
            i = i+dirs[d][0], j = j+dirs[d][1];
            
        };

        auto cur = head;
        while (cur != nullptr) {
            ans[i][j] = cur->val;
            next(); cur = cur->next;
        }

        return ans;        
    }
};