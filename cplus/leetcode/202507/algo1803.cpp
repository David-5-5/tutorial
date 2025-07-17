#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 6.4 字典树（trie）- 0-1 字典树（异或字典树）
struct Node {
    Node* son[2]{};
    int cnt = 0;
};

class Solution {
private:
    int hi = 14;
    Node* root = new Node();
    void insert(int val) {
        auto node = root;
        node->cnt ++;
        for (int i=hi; i>=0; --i) {
            int v = (val >> i) & 1;
            if (node->son[v] == nullptr) node->son[v] = new Node();
            node = node->son[v];
            node->cnt ++;
        }
    }

public:
    int countPairs(vector<int>& nums, int low, int high) {
        // 自行解答，统一设置上限
        int mx = ranges::max(nums);
        while ((1 << hi)>mx) hi--;

                
        int ans = 0;
        for (int i = 1; i<nums.size(); ++i) {

            insert(nums[i-1]);
            // 设置上限，按位递归求解 cnt，
            auto dfs = [&] (this auto&& dfs, Node* node, int res, int l, int limit) -> int {
                if (node->son[0] == nullptr && node->son[1] == nullptr) return node->cnt;
                int v = (nums[i] >> l) & 1, cnt = 0;
                if (node->son[v^1] != nullptr) 
                    if (res + (1<<l)*2 -1 <= limit) cnt += node->son[v^1]->cnt;
                    else if (res + (1<<l) <= limit) cnt += dfs(node->son[v^1], res+(1<<l), l-1, limit);
                if (node->son[v] != nullptr) 
                    if (res + (1<<l)*2 - 1 <= limit) cnt += node->son[v]->cnt;
                    else cnt += dfs(node->son[v], res, l-1, limit);
                
                return cnt;
            };
            ans += dfs(root, 0, hi, high) - dfs(root, 0, hi, low-1);
        }

        return ans;
    }

    int countPairs2(vector<int>& nums, int low, int high) {
        // simiar to countPairs
        int mx = ranges::max(nums);
        while ((1 << hi)>mx) hi--;

                
        int ans = 0;
        for (int i = 1; i<nums.size(); ++i) {

            insert(nums[i-1]);
            // 根据上下限，按位递归求解 cnt，这样写法比仅设置上限复杂
            auto dfs = [&] (this auto&& dfs, Node* node, int res, int l) -> int {
                if (node->son[0] == nullptr && node->son[1] == nullptr) return node->cnt;
                int v = (nums[i] >> l) & 1, cnt = 0;
                if (node->son[v^1] != nullptr) 
                    if (res+(1<<l)>=low && res + (1<<l)*2 -1 <= high) cnt += node->son[v^1]->cnt;
                    else if (res + (1<<l) <= high) cnt += dfs(node->son[v^1], res+(1<<l), l-1);
                if (node->son[v] != nullptr) 
                    if (res>=low && res + (1<<l) - 1 <= high) cnt += node->son[v]->cnt;
                    else if (res + (1<<l) - 1 >= low)  cnt += dfs(node->son[v], res, l-1);
                
                return cnt;
            };
            ans += dfs(root, 0, hi);
        }

        return ans;
    }


    int countPairs3(vector<int>& nums, int low, int high) {
        int mx = max(high, ranges::max(nums));
        while ((1 << hi)>mx) hi--;
                
        int ans = 0;
        for (int i = 1; i<nums.size(); ++i) {
            insert(nums[i-1]);
            
            auto cnt = [&](int val, int limit) -> int {
                auto cur = root;
                int sum = 0;
                for (int i=hi; i>=0; --i) {
                    int b = (val >> i) & 1;
                    if ((limit>>i) & 1 ) {  // limit bit = 1
                        if (cur->son[b] != nullptr) sum += cur->son[b]->cnt;    // 肯定小于 limit 全包括
                        if (cur->son[b^1] != nullptr) cur = cur->son[b^1];
                        else return sum;
                    } else {                // limit bit = 0
                        if (cur->son[b] == nullptr) return sum;
                        cur = cur->son[b];
                    }
                }
                sum += cur->cnt;        // 不能忽略
                return sum;
            };
            ans += cnt(nums[i], high) - cnt(nums[i], low-1);
        }

        return ans;
    }
};


int main() {
    vector<int> nums = {1,4,2,7};
    cout << Solution().countPairs2(nums, 2, 6) << endl;
}