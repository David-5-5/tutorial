#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索
class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        // 自行解答，觉得代码很丑陋
        auto dfs = [&](this auto&& dfs, vector<double> c) -> bool {
            if (c.size() == 1)  return fabs(c.back() - 24) <  1e-9;

            for (int i=0; i<c.size()-1; ++i) for (int j=i+1; j<c.size(); ++j) {
                vector<double> left; for (int k=0; k<c.size(); ++k) if (k!=i && k!=j) left.push_back(c[k]);
                left.push_back(-0.0);
                left[left.size()-1] = c[i]+c[j];
                if(dfs(left)) return true;
                left[left.size()-1] = c[i]*c[j];
                if(dfs(left)) return true;
                left[left.size()-1] = c[i]-c[j];
                if(dfs(left)) return true;
                left[left.size()-1] = c[j]-c[i];
                if(dfs(left)) return true;
                left[left.size()-1] = c[i]/c[j];
                if(dfs(left)) return true;
                left[left.size()-1] = c[j]/c[i];
                if(dfs(left)) return true;
            }
            return false;
        };

        return dfs(vector<double>(cards.begin(), cards.end()));     
    }
};