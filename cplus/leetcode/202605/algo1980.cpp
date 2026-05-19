#include <bits/stdc++.h>
using namespace std;

// 六、构造题
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        // 暴力 
        unordered_set<int> num_hash; int n = nums.size();
        for (auto & s: nums) num_hash.insert(stoi(s, nullptr, 2));

        for (int i=0; i<=n; i++) {
            // bitset 整数转固定长度二进制字符串
            if (!num_hash.count(i)) return bitset<16>(i).to_string().substr(16-n);
        }
        return "";
    }

    string findDifferentBinaryString(vector<string>& nums) {
        // 康托对角线 
        string ans = ""; int n = nums.size();
        for (int i=0; i<n; i++) {
            ans.push_back(((nums[i][i]-'0')^1)+'0');
        }
        return ans;  

    }
};