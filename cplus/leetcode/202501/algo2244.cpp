class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        // 自行解答
        map<int, int> cnt;
        for (int t : tasks)
            cnt[t] += 1;
        
        int ans = 0;
        for (auto it=cnt.begin(); it!=cnt.end(); ++it) {
            if (it->second == 1) return -1;
            ans += (it->second + 2) / 3; // 上取整
        }

        return ans;
    }
};