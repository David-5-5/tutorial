#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.3 并查集 - GCD 并查集
// 数学算法 - 数论 - 1.3 质因数分解
class UnionFind {
    vector<int> fa;
public:
    int cc;         // 连通块个数
    UnionFind(int n): fa(n), cc(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y; cc--;
        }
    }
};

// 计算最小质因子
int N = 1e5+1;
vector<int> min_prime_factor(N);
int init = [] {
    iota(min_prime_factor.begin(), min_prime_factor.end(), 0);
    for (int i = 2; i <= sqrt(N); ++i) {
        if (min_prime_factor[i] == i) {
            for (int j = i * i; j < N; j += i) {
                min_prime_factor[j] = i;
            }
        }
    }
    return 0;
}();

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        // 自行解答
        unordered_map<int, int> mp;
        int n = nums.size();
        UnionFind uf(n);
        for (int i=0;i<n;++i){
            auto x = nums[i];
            while (x>1){
                auto p = min_prime_factor[x];
                if (mp.count(p)){
                    uf.merge(i, mp[p]);
                } else mp[p] = i;
                while (x%p==0){
                    x/=p;
                }
            }
        }
        if (uf.cc == 1) return true;

        unordered_map<int, vector<int>> grp_inx;
        unordered_map<int, vector<int>> grp_nums;
        for (int i=0;i<n;++i){
            auto root = uf.find(i);
            grp_inx[root].push_back(i);
            grp_nums[root].push_back(nums[i]);
        }
        vector<int> sorted(n);
        for (auto &[root, inx]: grp_inx){
            sort(grp_nums[root].begin(), grp_nums[root].end());
            for (int i=0;i<inx.size();++i){
                sorted[inx[i]] = grp_nums[root][i];
            }
        }
        for (int i=1;i<n;++i){
            if (sorted[i-1]>sorted[i]) return false;
        }
        return true;
    }
};