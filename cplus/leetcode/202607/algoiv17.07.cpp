#include <bits/stdc++.h>
using namespace std;


class Solution {
private:
    unordered_map<string, string> fa;

    string find(string& name) {
        if (fa.count(name) == 0) {
            fa[name] = name;
        }
        if (fa[name] != name)  {
            fa[name] = find(fa[name]);
        }
        return fa[name];
    }

    void merge(string from, string to) {
        auto x = find(from), y = find(to);
        if (x != y) {
            if (y > x) swap(x, y);
            fa[x] = y;
        } 
    }

public:
    vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms) {

        for (auto syn: synonyms) {
            auto pos = syn.find(",");
            auto n1 = syn.substr(1, pos-1), n2 = syn.substr(pos+1, syn.length()-pos-2);

            auto fa1 = find(n1), fa2 = find(n2);
            if (fa1 != fa2) {
                merge(fa1, fa2);
            }
        }
        
        unordered_map<string, int> syn_cnt;

        for (int i=0; i<names.size(); i++) {
            auto pos = names[i].find('(');
            auto name = names[i].substr(0, pos);
            auto cnt = stoi(names[i].substr(pos+1, names[i].length() - pos -2));
            auto syn = find(name); syn_cnt[syn] += cnt;
        }

        vector<string> ans;
        for (auto [syn, cnt]: syn_cnt) {
            // ans.emplace_back(syn + "(" + to_string(cnt) + ")");
            ans.emplace_back(format("{}({})", syn, cnt));   // c++ 20
        }
        return ans;
    }
};