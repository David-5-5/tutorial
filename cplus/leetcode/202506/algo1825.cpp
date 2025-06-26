#include <bits/stdc++.h>
using namespace std;

class MKAverage {
// 使用 Python SortedList 翻译过来，但是超时，python 可以
private:
    int m, k;
    long sum;
    vector<int> nums;
    multiset<pair<int, int>> sorted;  // 使用 multiset 维护有序对

public:
    MKAverage(int m, int k) : m(m), k(k), sum(0) {}
    
    void addElement(int num) {
        nums.push_back(num);
        int idx = nums.size() - 1;
        
        if (nums.size() <= m) {
            // 窗口未满时，直接插入并维护有序列表
            sorted.insert({num, idx});
            if (nums.size() == m) {
                // 窗口满时，计算初始中间和
                auto it = sorted.begin();
                advance(it, k);  // 移动到第k个元素
                for (int i = 0; i < m - 2 * k; ++i) {
                    sum += it->first;
                    ++it;
                }
            }
        } else {
            // 窗口已满，移除最旧元素，添加新元素
            int out_idx = idx - m;
            int out_num = nums[out_idx];
            
            // 查找并移除最旧元素
            auto rm_it = sorted.find({out_num, out_idx});
            int rm_pos = distance(sorted.begin(), rm_it);
            
            // 根据移除元素的位置调整总和
            if (k <= rm_pos && rm_pos <= m - k - 1) {
                auto it = sorted.end();
                advance(it, -(m - k));  // 指向第 m-k 个元素
                sum += it->first - rm_it->first;
            } else if (rm_pos < k) {
                auto it1 = sorted.end();
                advance(it1, -(m - k));  // 指向第 m-k 个元素
                auto it2 = sorted.begin();
                advance(it2, k - 1);  // 指向第 k-1 个元素
                sum += it1->first - it2->first;
            }
            
            sorted.erase(rm_it);
            
            // 插入新元素
            auto ins_it = sorted.lower_bound({num, idx});
            int ins_pos = distance(sorted.begin(), ins_it);
            sorted.insert(ins_it, {num, idx});
            
            // 根据新元素的位置调整总和
            if (k <= ins_pos && ins_pos <= m - k - 1) {
                auto it = sorted.end();
                advance(it, -(m - k - 1));  // 指向第 m-k-1 个元素
                sum += num - it->first;
            } else if (ins_pos < k) {
                auto it1 = sorted.begin();
                advance(it1, k);  // 指向第 k 个元素
                auto it2 = sorted.end();
                advance(it2, -(m - k - 1));  // 指向第 m-k-1 个元素
                sum += it1->first - it2->first;
            }
        }
    }
    
    int calculateMKAverage() {
        if (nums.size() < m) return -1;
        return sum / (m - 2 * k);
    }
};


class MKAverage {
private:
    int m, k;
    long sum;
    vector<int> nums;
    set<pair<int, int>> left, mid, right;  // 使用 multiset 维护有序对

public:
    MKAverage(int m, int k) : m(m), k(k), sum(0) {}
    
    void addElement(int num) {
        nums.push_back(num);
        right.insert({num, nums.size()-1});
        if (nums.size() <= m) {
            if (right.size() > k) {
                mid.insert(*right.begin());
                right.erase(*right.begin());
            }
            if (mid.size() > m - 2 * k) {
                left.insert(*mid.begin());
                mid.erase(*mid.begin());
            }
            if (nums.size() == m) {
                for (auto it=mid.begin(); it!=mid.end(); ++it) sum += it->first;
            }
        } else {
            int inx = nums.size() - m - 1;
            if (right.count({nums[inx], inx})) right.erase({nums[inx], inx});
            if (mid.count({nums[inx], inx})) {
                mid.erase({nums[inx], inx}); sum -= nums[inx];
            }
            if (left.count({nums[inx], inx})) left.erase({nums[inx], inx});

            if (right.size() > k) {
                sum += right.begin()->first;
                mid.insert(*right.begin());
                right.erase(*right.begin());
            } else if (right.begin()->first < mid.rbegin()->first) {
                sum += right.begin()->first - mid.rbegin()->first;
                mid.insert(*right.begin());
                right.erase(*right.begin());
                right.insert(*mid.rbegin());
                mid.erase(*mid.rbegin());
            }
            if (mid.size() > m - 2 * k) {
                sum -= mid.begin()->first;
                left.insert(*mid.begin());
                mid.erase(*mid.begin());
            } else if (mid.begin()->first < left.rbegin()->first) {
                sum += left.rbegin()->first - mid.begin()->first;
                left.insert(*mid.begin());
                mid.erase(*mid.begin());
                mid.insert(*left.rbegin());
                left.erase(*left.rbegin());
            }
        }
    }
    
    int calculateMKAverage() {
        if (nums.size() < m) return -1;
        return sum / (m - 2 * k);        
    }
};


class MKAverage {
    // using multiset and uni-element
private:
    int m, k;
    long sum;
    vector<int> nums;
    multiset<int> left, mid, right;  // 使用 multiset 维护有序对

public:
    MKAverage(int m, int k) : m(m), k(k), sum(0) {}
    
    void addElement(int num) {
        nums.push_back(num);
        right.insert(num);
        if (nums.size() <= m) {
            if (right.size() > k) {
                mid.insert(*right.begin());
                right.erase(right.begin());
            }
            if (mid.size() > m - 2 * k) {
                left.insert(*mid.begin());
                mid.erase(mid.begin());
            }
            if (nums.size() == m) {
                for (auto it=mid.begin(); it!=mid.end(); ++it) sum += *it;
            }
        } else {
            int inx = nums.size() - m - 1;
            if (right.find(nums[inx])!=right.end()) right.erase(right.find(nums[inx]));
            else if (mid.find(nums[inx])!=mid.end()) {
                mid.erase(mid.find(nums[inx])); sum -= nums[inx];
            } else  left.erase(left.find(nums[inx]));

            if (right.size() > k) {
                sum += *right.begin();
                mid.insert(*right.begin());
                right.erase(right.begin());
            } else if (*right.begin() < *mid.rbegin()) {
                sum += *right.begin() - *mid.rbegin();
                mid.insert(*right.begin());
                right.erase(right.begin());
                right.insert(*mid.rbegin());
                mid.erase(prev(mid.end()));
            }
            if (mid.size() > m - 2 * k) {
                sum -= *mid.begin();
                left.insert(*mid.begin());
                mid.erase(mid.begin());
            } else if (*mid.begin() < *left.rbegin()) {
                sum += *left.rbegin() - *mid.begin();
                left.insert(*mid.begin());
                mid.erase(mid.begin());
                mid.insert(*left.rbegin());
                left.erase(prev(left.end()));
            }
        }
    }
    
    int calculateMKAverage() {
        if (nums.size() < m) return -1;
        return sum / (m - 2 * k);        
    }
};
/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */