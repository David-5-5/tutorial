#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.10 综合应用
class AllOne {
private:
    list<pair<unordered_set<string>, int>> lst;
    unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> nodes;
public:
    AllOne() {
        
    }
    
    void inc(string key) {
        if (nodes.count(key)) {
            // 在列表中
            auto cur = nodes[key], nxt = next(cur);
            if (nxt == lst.end() || nxt->second > cur->second + 1) {
                unordered_set<string> s({key});
                nodes[key] = lst.emplace(nxt, s, cur->second + 1);
            } else {
                nxt->first.emplace(key); nodes[key] = nxt;
            }
            cur->first.erase(key);
            if (cur->first.empty()) lst.erase(cur);
        }else {
            if (lst.empty() || lst.begin()->second > 1) {
                unordered_set<string> s({key});
                lst.emplace(lst.begin(), s, 1);
            } else {
                lst.begin()->first.emplace(key);
            }
            nodes[key] = lst.begin();
        }
    }
    
    void dec(string key) {
        auto cur = nodes[key], pre = prev(cur);
        if (cur->second == 1) nodes.erase(key);
        else if (cur == lst.begin() || pre->second < cur->second-1) {
            unordered_set<string> s({key});
            nodes[key] = lst.emplace(cur, s, cur->second-1);
        } else {
            pre->first.emplace(key); nodes[key] = pre;
        }
        cur->first.erase(key);
        if (cur->first.empty()) lst.erase(cur);
    }
    
    string getMaxKey() {
        return lst.empty()?"":*lst.rbegin()->first.begin();
    }
    
    string getMinKey() {
        return lst.empty()?"":*lst.begin()->first.begin();
    }
};


/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */