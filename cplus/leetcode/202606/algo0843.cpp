#include <bits/stdc++.h>
using namespace std;

// 贪心 - 七、交互题
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class Master {
   public:
      int guess(string word);
};

class Solution {
public:
    void findSecretWord(vector<string>& words, Master& master) {
        // 参考题解，极小化极大值
        vector<string> candicate(words);

        auto similiar = [](string& a, string& b) -> int {
            int cnt = 0;
            for (int i=0; i<6; i++) if (a[i] == b[i]) cnt ++;
            return cnt;
        };

        for (int _=0; _<30; _++) {
            int n = candicate.size(), inx = 0, minmax = n;
            for (int i=0; i<n; i++) {                
                vector<int> sim(n), freq(6);
                for (int j=0; j<n; j++) {
                    if (i == j) continue;
                    sim[j] = similiar(candicate[i], candicate[j]);
                    freq[sim[j]] ++;
                }
                auto mx = ranges::max(freq);
                if (mx < minmax) minmax = mx, inx = i;
            }
            cout << candicate[inx] << endl;
            auto gus = master.guess(candicate[inx]);
            if (gus == 6) return;
            vector<string> nxt;
            for (int j=0; j<n; j++)
                if (inx!=j && similiar(candicate[inx], candicate[j]) == gus)
                    nxt.push_back(candicate[j]);
            
            candicate = move(nxt);  
        }
    }
};