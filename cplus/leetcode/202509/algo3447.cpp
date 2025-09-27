#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
int lpf[N];

int init = [] {
    memset(lpf, 0, sizeof(lpf));

    for (int i = 2; i < N; ++i) {      
        if (lpf[i] == 0) { // 质数
            for (int j = i; j < N; j += i) {
                if (lpf[j] == 0) lpf[j] = i;   // 质数 x 的 lpf(x) == x
            }
        }
    }
    return 0;
}();

unordered_map<int, vector<int>> all_factors;

// prime_factor(45) = {{3,2}, {5,1}} 45 = 3^2 * 5^1
// prime_factor(16) = {{2,4}} = 2^4
vector<pair<int, int>> prime_factors(int x) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = lpf[x], e = 1;
        for (x/=p; x % p == 0; x /= p) e ++;
        res.emplace_back(p, e);
    }
    return res;
}

// 获取从 1 到 x 所有因子
vector<int> get_all_factors(int x) {
    if (all_factors.count(x)) return all_factors[x];

    vector<pair<int,int>> primes = prime_factors(x);

    auto dfs = [&](this auto&& dfs, int i, vector<int>& factors) -> void {
        if (i == primes.size()) return;
        auto [val, cnt] = primes[i];
        vector<int> ext;
        for (int i=0; i<cnt; ++i) {
            for (auto v:factors) ext.emplace_back(v*val);
            val *= val;
        }

        factors.insert(factors.end(), ext.begin(), ext.end());
        dfs(i+1, factors);
    };
    vector<int> factors = {1};
    dfs(0, factors); return all_factors[x]= factors;
}


// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        // 自行解答
        unordered_map<int, int> ele_inx; int m = elements.size();
        for (int i=m-1; i>=0; --i) 
            ele_inx[elements[i]] = i;
        
        vector<int> ans; 
        for (int i=0; i<groups.size(); ++i) {
            int inx = m, x = groups[i];
            
            for (int f=1; f*f<=x; ++f) if(x % f ==0) {
                if (ele_inx.count(f)) {
                    inx = min(inx, ele_inx[f]);
                }
                if (ele_inx.count(x/f)) {
                    inx = min(inx, ele_inx[x/f]);
                }
            }
            ans.push_back(inx<m?inx:-1);
        }

        return ans;  
    }

    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        // 自行解答 反而慢了
        unordered_map<int, int> ele_inx; int m = elements.size();
        for (int i=m-1; i>=0; --i) 
            ele_inx[elements[i]] = i;
        
        vector<int> ans; 
        for (int i=0; i<groups.size(); ++i) {
            int inx = m, x = groups[i];
            vector<int> factors = get_all_factors(x);
            for (auto f: factors) 
                if (ele_inx.count(f)) 
                    inx = min(inx, ele_inx[f]);
            ans.push_back(inx<m?inx:-1);
        }
        return ans;
    }

    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        // 参考题解
        int mx = ranges::max(groups); vector<int> target(mx+1, -1);
        for (int i=0; i<elements.size(); ++i) {
            int x = elements[i];
            if (x > mx || target[x] >= 0) continue;
            for (int y = x; y <=mx; y+=x) if (target[y]<0) target[y] = i;
        }
        for (int &x:groups) x = target[x];
        return groups;
    }    

};