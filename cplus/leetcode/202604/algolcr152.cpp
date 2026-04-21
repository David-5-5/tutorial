#include <bits/stdc++.h>
using namespace std;

// LCR series 经典算法
class Solution {
public:
    bool verifyTreeOrder(vector<int>& postorder) {
        
        // 二分法 O(N^2)
        int n = postorder.size();

        auto dfs = [&](this auto&& dfs, int l, int r) -> bool {
            if (l >= r) return true;
            auto root = postorder[r], p = l;
            while (postorder[p] < root) p ++;
            auto m = p;
            while (postorder[p] > root) p ++ ;
            return p == r &&  dfs(l, m-1) && dfs(m, r-1);
        };
        
        return dfs(0, n-1);
    }

    bool verifyTreeOrder(vector<int>& postorder) {
        // 单调栈 O(N) 判断搜索树的后序  
        int n = postorder.size();

        stack<int> st; int root = INT_MAX;

        for (int i = n-1; i>=0; i--) {
            if (postorder[i] > root) return false;
            while (st.size() && st.top() > postorder[i]) {
                root = st.top(); st.pop();
            }
            st.push(postorder[i]);
        }        
        return true;
    }    
};