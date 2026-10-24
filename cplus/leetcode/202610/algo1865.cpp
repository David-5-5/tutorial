#include <bits/stdc++.h>
using namespace std;

class FindSumPairs {
private:
    vector<int>nums1, nums2;
    unordered_map<int, int> cnt2;
    unordered_map<int, int> cnt1;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2): nums1(nums1), nums2(nums2) {
        for (auto & v: nums2) cnt2[v] ++;
        for (auto & v: nums1) cnt1[v] ++;
    }
    
    void add(int index, int val) {
        cnt2[nums2[index]] --;
        nums2[index] += val;
        cnt2[nums2[index]] ++;
    }
    
    int count(int tot) {
        int res = 0;
        for (auto &[k, v]: cnt1) {
            if (tot - k < 0) continue;  // 避免无效hash查找
            res += v * cnt2[tot-k];
        }
        return res;
    }
};

class FindSumPairs {
private:
    vector<int>nums1, nums2;
    unordered_map<int, int> cnt2;
    unordered_map<int, int> cnt1;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2): nums1(nums1), nums2(nums2) {
        for (auto & v: nums2) cnt2[v] ++;
        for (auto & v: nums1) cnt1[v] ++;
    }
    
    void add(int index, int val) {
        cnt2[nums2[index]] --;
        nums2[index] += val;
        cnt2[nums2[index]] ++;
    }
    
    int count(int tot) {
        int res = 0;
        for (auto it = cnt1.begin(); it!=cnt1.end(); it ++) {
            if (it->first > tot) continue;
            auto it2 = cnt2.find(tot - it->first);
            if (it2 != cnt2.end()) res += it->second * it2->second;
        }
        return res;
    }
};


/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */