#include <bits/stdc++.h>
using namespace std;

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> times;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        times[key].emplace_back(timestamp, value);
    }
    
    string get(string key, int timestamp) {
        auto target = pair{timestamp, ""};
        auto it = upper_bound(times[key].begin(),times[key].end(), target, 
            [](const pair<int, string>& a, const pair<int, string>& b) {
                return a.first < b.first;
            });
        if (it == times[key].begin()) return "";
        else return prev(it)->second;
    }
};


/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */