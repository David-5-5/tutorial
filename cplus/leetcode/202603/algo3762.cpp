#include <bits/stdc++.h>
using namespace std;

// 主席树，持久化线段树 模板 独立类
// Dynamic Segment Tree  (Dynamic Node Allocation Segment Tree)
class Node {
    int l, r;            //  区间
    Node *left, *right;  //  左右子树
    int cnt;
    void maintain() {
        cnt = left->cnt + right->cnt;
        sum = left->sum + right->sum;
    }
public:
    long long sum;
    Node(int l, int r, Node* left = nullptr, Node* right = nullptr, int cnt = 0, long long sum = 0)
        : l(l), r(r), left(left), right(right), cnt(cnt), sum(sum) {}

    static Node* build(int l, int r) {
        Node* node = new Node(l, r);
        if (l != r) {
            int m = (l + r) / 2;
            node->left = build(l, m);
            node->right = build(m+1, r);
        }
        return node;
    }

    Node* add(int i, int val) {
        Node * cur = new Node(l, r, left, right, cnt, sum);
        if (l == r) {
            cur->cnt += 1; cur->sum += val;
            return cur;
        }
        int m = (l + r) / 2; 
        if (i <= m) cur->left = cur->left->add(i, val);
        else cur->right = cur->right->add(i, val);
        cur->maintain();
        return cur;
    }

    int kth(Node* prev, int k) {
        if (l == r) return l;
        // 从根节点的视角，包括所有区间元素，因此应大于 k，因此先比较左子树的区间元素数量
        int rem = left->cnt - prev->left->cnt;
        if (rem >= k) return left->kth(prev->left, k);
        else return right->kth(prev->right, k - rem);
    }

    pair<int, long long> query(Node* prev, int m_rank) {
        if (r <= m_rank) return {cnt - prev->cnt, sum - prev->sum};
        auto [cnt, sum] = left->query(prev->left, m_rank);
        int m = (l + r) / 2;
        if (m_rank > m) {
            auto [r_cnt, r_sum] = right->query(prev->right, m_rank);
            cnt += r_cnt; sum += r_sum;
        }
        return {cnt, sum};
    }

};

// 四、数学贪心 - 4.5 中位数贪心
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // 复习
        int n = nums.size();
        vector<int> left(n);
        for (int i=1; i<n; i++) left[i] = nums[i] % k == nums[i-1] % k? left[i-1] : i;

        // 离散化 nums
        vector<int> uni_nums = nums;
        sort(uni_nums.begin(), uni_nums.end());
        uni_nums.erase(ranges::unique(uni_nums).begin(), uni_nums.end());   // distinct

        int m = uni_nums.size();
        vector<Node*> pst(n+1);  // persistent segment tree
        pst[0] = Node::build(0, m-1);   // 线段树的值域 [0, m)
        for (int i=0; i<n; i++) {
            int j = ranges::lower_bound(uni_nums, nums[i]) - uni_nums.begin();
            pst[i+1] = pst[i]->add(j, nums[i]);
        }

        vector<long long> ans;
        for (auto & q: queries) {
            auto l = q[0], r = q[1] + 1;
            if (left[r-1] > l) {ans.emplace_back(-1); continue;}

            int len = r - l;      // number of elements in interval
            int m_rank = pst[r]->kth(pst[l], len / 2 + 1);  // 中位数
            long long median = uni_nums[m_rank];
            // 求所有数与中位数的距离和，利用前缀和
            long long total = pst[r]->sum - pst[l]->sum;
            auto [l_cnt, l_sum] = pst[r]->query(pst[l], m_rank);
            
            long long res = median * l_cnt - l_sum;
            res += total - l_sum - median * (len-l_cnt);
            ans.emplace_back(res / k);
        } 
        return ans;
    }   
};