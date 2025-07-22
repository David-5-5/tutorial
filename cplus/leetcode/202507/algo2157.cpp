#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {
    vector<int> fa;
public:
    int cc;         // 连通块个数
    UnionFind(int n): fa(n), cc(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y; cc--;
        }
    }
};

class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        // 自行解答
        int n = words.size();
        // 按长度排序，方便处理，后续进行进行减字符及换字符操作 不需要排序，费时
        // sort(words.begin(), words.end(), [](const string a, const string b){
        //     return a.size() < b.size();
        // });
        unordered_map<int, int> mp;
        UnionFind uf(n);

        for (int i=0; i<n; ++i) {
            auto & word = words[i];
            
            int key = 0;
            for (char c: word) {
                key |= (1 << (c - 'a'));
            }
            if (mp.count(key)) {
                uf.merge(mp[key], i);
            }

            for (int k=0; k<26; ++k) {
                auto nkey = key ^ (1 << k);    // 添加或删除
                if (mp.count(nkey)) {
                    uf.merge(mp[nkey], i);
                }
                // !!!(key >> k) & 1) 加括号，否则会报错，因为优先级问题，导致结果不正确!!!
                if (((key >> k) & 1) == 0) continue;  // 删除后添加
                for (int l=0; l<26; ++l) {
                    if ((key >> l) & 1) continue;
                    auto nnkey = nkey | (1 << l);   // 加上第 l 位
                    if (mp.count(nnkey)) {
                        uf.merge(mp[nnkey], i);
                    }
                }
            }
            mp[key] = i;
        }

        int max_cnt = 0;
        unordered_map<int, int> cnt;
        for (int i=0; i<n; ++i) {
            cnt[uf.find(i)]++;
            max_cnt = max(max_cnt, cnt[uf.find(i)]);
        }
        return {uf.cc, max_cnt};
    }

};