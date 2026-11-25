#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        unordered_set<int> invIdx;

        int n = nums.size(); vector<pair<int, int>> links(n, {-1, 1}); // first: prev , second : next

        vector<long long> nnums(nums.begin(), nums.end());
        for (int i=1; i<n; i++) {
            links[i] = {i-1, i+1};  // initial prev/next ptr of link
            if (nnums[i-1] > nnums[i]) invIdx.insert(i-1);
            pq.emplace(nnums[i-1] + nnums[i], i-1);   // 相邻两数之和
        }
        
        int ans = 0; 
        while (!invIdx.empty()) {
            auto isValid = [&] () -> bool {
                auto [tot, idx] = pq.top();
                auto nxt = links[idx].second;
                if (nxt == -1 || nxt == n || links[nxt].second == -1 || tot != nnums[idx] + nnums[nxt])
                    return false;
                return true;
                
            };
            while (!isValid()) pq.pop();    // 删除 pq 中不合法
            auto [tot, idx] = pq.top(); pq.pop();

            auto prev = links[idx].first;
            if (prev != -1 && invIdx.count(prev)) 
                invIdx.erase(prev); // 和前序逆序对取消
            if (prev != -1 && nnums[prev] > tot) invIdx.insert(prev);
            if (prev != -1) pq.emplace(nnums[prev] + tot, prev);; // 重新计算和前序的和
            nnums[idx] = tot;

            if (invIdx.count(idx)) invIdx.erase(idx); // 和 next 合并，idx 逆序无效
            auto next = links[idx].second;
            if (invIdx.count(next)) invIdx.erase(next); // 和 next 合并，next 逆序无效
            auto nnext = links[next].second;
            links[idx].second = nnext;
            if(nnext != n) {
                links[nnext].first = idx;
                if (nnums[idx] > nnums[nnext]) invIdx.insert(idx);
                pq.emplace(0LL + nnums[idx] + nnums[nnext], idx);
            }
            links[next] = {-1, -1}; // merged，next is invalid
            ans += 1;
        }

        return ans;
    }
};

int main() {
    vector<int> nums = {5,2,3,1};
    cout << Solution().minimumPairRemoval(nums) << endl;
}