#include <bits/stdc++.h>
using namespace std;


// 回溯 - 4.6 有重复元素的回溯
set<long long> pal;

// 主函数：生成有重复元素的数组的所有不重复排列
void permuteUnique(int mask) {
    int mid = 0; vector<int> nums;
    for (int i=1; i<10; ++i) {
        if (((mask >> i) & 1) == 1) {
            for (int _=0; _<i/2; ++_) nums.push_back(i);
            if (i%2) mid = i;
        }
    }
    if (nums.empty()) return;

    // 排序：让相同元素相邻，为去重做准备
    sort(nums.begin(), nums.end());
    
    vector<bool> used(nums.size(), false); // 标记元素是否已使用
    vector<int> path; // 记录当前排列路径
    auto dfs = [&](this auto&& dfs, vector<int>& path) {
        if (path.size() == nums.size()) {
                long long val = 0;
                for (int i=0; i<path.size(); ++i) {
                    val = val * 10 + path[i];
                }
                if (mid) val = val * 10 + mid;
                for (int i=path.size()-1; i>=0; --i) {
                    val = val * 10 + path[i];
                }
                pal.insert(val);
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

            used[i] = true;
            path.push_back(nums[i]);

            dfs(path);
            path.pop_back();
            used[i] = false;
        }
    };
    dfs(path);
};

auto init = [] {
    vector<set<int>> masks(17);
    for (int i = 1; i<17; ++i) {
        if (i<10) masks[i].insert(1<<i);
        if (i % 2) {    // 奇数
            for (int x=1; x<=i/2; x++) {
                auto y = i - x;
                for (auto mx: masks[x]) for (auto my:masks[y]) {
                    if ((mx & my) == 0) masks[i].insert(mx | my);
                }
            }
        } else {        // 偶数
            for (int x = 2; x<i/2; x+=2) {
                auto y = i - x;
                for (auto mx: masks[x]) for (auto my:masks[y]) {
                    if ((mx & my) == 0) masks[i].insert(mx | my);
                }
            }
        }
        
    }
    pal.insert(1); pal.insert(22);
    for (int i=3; i<17; ++i) for(auto& mask:masks[i]) permuteUnique(mask);
    return 0;
}();
class Solution {
public:
    long long specialPalindrome(long long n) {
        return *pal.upper_bound(n);
    }
};