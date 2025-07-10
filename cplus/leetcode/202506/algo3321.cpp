#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.7 堆 - 对顶堆（滑动窗口第 K 小/大）
class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        // 自行解答，不过代码太混乱了，需要结构优化
        int n = nums.size();
        vector<long long> ans(n-k+1);

        unordered_map<int, int> cnt;
        multiset<pair<int,int>> left, right;
        
        auto compare = [&](pair<int, int> r, pair<int, int> l) -> bool {
            if (r.first > l.first) return true;
            if (r.first == l.first) return r.second > l.second;
            return false;
        };
        long long rightSum = 0;

        auto append = [&](int u) {
            if (cnt[u]) {
                if (right.find({cnt[u], u}) != right.end()) {
                    rightSum += u;
                    right.erase(right.find({cnt[u], u}));
                    right.emplace(++cnt[u], u);
                } else {
                    left.erase(left.find({cnt[u], u}));
                    left.emplace(++cnt[u], u);
                }
            } else {rightSum += u;right.emplace(++cnt[u], u);}

            if (right.size() > x) {
                rightSum -= right.begin()->first * right.begin()->second;
                left.emplace(*right.begin()); right.erase(right.begin());
            } else if (right.size() == x && left.size() && !compare(*right.begin(), *left.rbegin())){
                rightSum +=  (long) left.rbegin()->first * left.rbegin()->second -(long)  right.begin()->first * right.begin()->second;
                right.emplace(*left.rbegin()); left.erase(prev(left.end()));
                left.emplace(*right.begin()); right.erase(right.begin());
            }
        };

        for (int i=0; i<k-1; ++i) {
            append(nums[i]);
        }

        for (int i=k-1; i<n; ++i) {
            append(nums[i]); 
            ans[i-k+1] = rightSum;

            int v = nums[i-k+1];    // 出队列
            if (right.find({cnt[v], v}) != right.end()) {
                rightSum -= v;
                right.erase(right.find({cnt[v], v}));
                if (--cnt[v]) right.emplace(cnt[v], v);

                if (right.size() < x && left.size()) {
                    rightSum += (long) left.rbegin()->first * left.rbegin()->second;
                    right.emplace(*left.rbegin()); left.erase(prev(left.end()));
                } else if (left.size() && !compare(*right.begin(), *left.rbegin())){
                    rightSum += (long)  left.rbegin()->first * left.rbegin()->second - (long) right.begin()->first * right.begin()->second;
                    right.emplace(*left.rbegin()); left.erase(prev(left.end()));
                    left.emplace(*right.begin()); right.erase(right.begin());
                }
            } else {
                left.erase(left.find({cnt[v], v}));
                if (--cnt[v]) left.emplace(cnt[v], v);
            }

        }
        return ans;
    }
};

int main() {
    vector<int> nums = {1,6,5,5,5};
    Solution().findXSum(nums, 2, 1);
}