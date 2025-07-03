#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 参考题解，方法一：快慢指针
        int slow = 0, quick = 0;
        do {
            slow = nums[slow];
            quick = nums[nums[quick]];
        }while (slow != quick);

        slow = 0;
        while (slow != quick) { // 都走一步
            slow = nums[slow];
            quick = nums[quick];
        }
        
        return slow;
    }
};