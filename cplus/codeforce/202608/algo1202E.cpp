#include <bits/stdc++.h>
using namespace std;

// AC 自动机
struct Node {
    Node* son[26]{};
    Node* fail;
    bool end = false;
    long long cnt = 0;
};


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    string t; int n;
    cin >> t; cin >> n;
    vector<string> s(n);
    for (int i=0; i<n; i++) cin >> s[i];

    int m = t.length();
    auto build = [&](bool rev) -> vector<long long> {
        Node* root = new Node();
        for (auto word: s) {
            if (rev) reverse(word.begin(), word.end());
            auto node = root;
            for (auto & c: word) {
                if (node->son[c-'a'] == nullptr) node->son[c-'a'] = new Node();
                node = node->son[c-'a'];            
            }
            node->end = true; node->cnt ++;
        }
        
        root-> fail = root;
        queue<Node*> q;
        for (int i=0; i<26; i++) {
            
            if (root->son[i] != nullptr) {
                root->son[i]->fail = root; q.emplace(root->son[i]);
            } else root->son[i] = root;
        }
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            node->end = node->end || node->fail->end;
            // "aaa"->cnt += "aa"->cnt "aa"->cnt += "a"->cnt
            // 以 i 为结尾的模式串的数量
            node->cnt += node->fail->cnt;
            for (int i=0; i<26; i++) {
                if (node->son[i] != nullptr) {
                    node->son[i]->fail = node->fail->son[i];
                    q.emplace(node->son[i]);
                } else node->son[i] = node->fail->son[i];
            }
        }


        vector<long long> arr(m);
        auto cur = root;
        if (rev) reverse(t.begin(), t.end());
        for (int i=0; i<m; i++) {
            auto &ch = t[i];
            cur = cur->son[ch - 'a'];
            arr[i] = cur->cnt;
        }

        if (rev) reverse(arr.begin(), arr.end());
        return arr;
    };


    auto prefix = build(false);
    auto suffix = build(true);

    long long ans = 0;

    for (int i=0; i<m-1; i++) ans += prefix[i] * suffix[i+1];
    cout << ans << endl; 
    return 0;

}