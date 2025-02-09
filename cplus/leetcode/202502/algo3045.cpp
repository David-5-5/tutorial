#include <bits/stdc++.h>
using namespace std;

// The Trie class
struct Node {
    Node *son[26]{};
    int cnt = 0;
};

// 周赛 385
class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        // 参考题解 
        long ans = 0;
        Node* root = new Node();
        // z 函数 模板
        auto zFunc = [&](string text) -> vector<int>{
            int t_len = (int)text.length();
            vector<int> ans(t_len);
            for (int i = 1, l = 0, r = 0; i < t_len; ++i) {
                if (i <= r && ans[i - l] < r - i + 1) {
                    ans[i] = ans[i - l];
                } else {
                    ans[i] = max(0, r - i + 1);
                    while (i + ans[i] < t_len && text[ans[i]] == text[i + ans[i]]) ++ans[i];
                }
                if (i + ans[i] - 1 > r) l = i, r = i + ans[i] - 1;
            }
            return ans;
        };


        for (auto& w: words) {
            vector<int> z = zFunc(w);
            int n = w.size();
            z[0] = n;
            auto cur = root;
            for (int i=0; i<n; i++) {
                int ch = w[i] - 'a'; // 字符的序号 a=0,b=1,.. z=25
                if (cur->son[ch] == nullptr) {
                    cur->son[ch] = new Node();
                }
                cur = cur->son[ch];
                if (z[n-i-1] == i+1) {
                    ans += cur->cnt;
                }
            }
            cur->cnt++;
        }

        return ans;
    }
};