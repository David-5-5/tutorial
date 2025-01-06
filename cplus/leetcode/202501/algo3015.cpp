class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        // 自行解答
        vector<int> ans(n);
        for (int i=1; i<n; i++) {
            for (int j=i+1; j<=n; j++) {
                int dis = min(j-i, abs(min(x,y)-i)+abs(j-max(x,y))+1);
                ans[dis-1] += 2;
            }
        }

        return ans;
    }
};