#include <bits/stdc++.h>
using namespace std;

// 有序集合 - 自行解答
class MovieRentingSystem {
    unordered_map<int, set<pair<int, int>>> avail;
    set<tuple<int, int, int>> rented;
    unordered_map<long long, int> prices;

    long long key(int shop, int movie) {
        return (long long) shop << 32 | movie;
    }

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto e: entries) {
            int shop = e[0], movie = e[1], price = e[2];
            avail[movie].emplace(price, shop);
            
            prices[key(shop, movie)] = price;
        }
    }
    
    vector<int> search(int movie) {
        vector<int> ans;
        for (auto it=avail[movie].begin(); it!=avail[movie].end() && ans.size()<5; ++it) {
            ans.push_back(it->second);
        }
        return ans;
    }
    
    void rent(int shop, int movie) {
        int price = prices[key(shop, movie)];
        rented.emplace(price, shop, movie);
        avail[movie].erase(avail[movie].find({price, shop}));
    }
    
    void drop(int shop, int movie) {
        int price = prices[key(shop, movie)];
        rented.erase(rented.find({price, shop, movie}));
        avail[movie].emplace(price, shop);
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> ans;
        for (auto it=rented.begin(); it!=rented.end() && ans.size()<5; ++it) {
            ans.push_back({get<1>(*it), get<2>(*it)});
        }
        return ans;        
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */