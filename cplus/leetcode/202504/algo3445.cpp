#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int maxDifference(string s, int k) {
        // 自行解答，分值2694, 接近2700，给自己点个赞
        int n = s.size();
        vector<vector<int>> pres(5, vector<int>(n+1));

        // 计算每个数字的前缀和
        for(int i=0; i<n; ++i) {
            int v = s[i] - '0';
            for (int j=0; j<5; ++j) {
                if (j==v) pres[j][i+1] = pres[j][i] + 1;
                else pres[j][i+1] = pres[j][i];
            }
        }

        int ans = INT_MIN;
        for (int a=0; a<5; ++a) for (int b=0; b<5; ++b) {       // 枚举 a 和 b
            if (a == b || pres[a][n] == 0 || pres[b][n] == 0) continue;

            // 记录 a - b 的最小值，以求出区间 a - b 的最大值
            // 同时要求满足取箭内 a 为奇数，b 为偶数，因此按照 a b 的奇偶性共 4 种情况
            // 同时要求区间的长度必须大于 k ，因此通过单调队列记录递减的 a-b 的最小值
            vector<deque<pair<int,int>>> queue(4, deque<pair<int,int>>());

            for (int i=1; i<=n; i++) {

                int val = pres[a][i] - pres[b][i];

                if (pres[a][i]%2==1 && pres[b][i] && pres[b][i]%2==0 && i>=k) ans = max(ans, val);

                int cur = ((pres[a][i]%2) << 1) + (pres[b][i] % 2);         // a b 奇偶性计算
                
                // a b 的前序奇偶性，a 奇偶性相反，保证区间内 a 的数量为奇数
                //                 b 奇偶性相同，保证区间内 b 的数量为偶数
                int prev = ((1 ^ pres[a][i]%2 )<< 1) + (pres[b][i] % 2);    

                // 若i - 第二个元素的下标 >= k, 队首出列，保证后续得到符合要求的最小值
                while (queue[prev].size()>1 && i-queue[prev][1].first>=k) {
                    queue[prev].pop_front();
                }
                
                if (queue[prev].size() && i-queue[prev].front().first>=k
                        && (pres[b][i]-pres[b][queue[prev].front().first])) // 区间内 b 不为 0
                    ans = max(ans, val - queue[prev].front().second);
                
                if (queue[cur].size()==0 || queue[cur].back().second > val)
                    queue[cur].emplace_back(i, val);                        // 当前最小值入队列

            }
    
        }
        return ans;       
    }
};

int main() {
    cout << Solution().maxDifference("44114402", 7) << endl;
}