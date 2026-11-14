#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        // 分别计算两个指针的哈希值
        size_t hash1 = std::hash<int>()(p.first);
        size_t hash2 = std::hash<int>()(p.second);
        
        // 组合两个哈希值（避免碰撞的简单方式）
        return hash1 ^ (hash2 << 1);
    }
}; 

class AuctionSystem {
private:
    unordered_map<pair<int, int>, int, PairHash> bids;
    unordered_map<int, vector<pair<int, int>>> mx_bid;
public:
    AuctionSystem() {
        
    }
    
    void addBid(int userId, int itemId, int bidAmount) {
        updateBid(userId, itemId, bidAmount);
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        bids[{userId, itemId}] = newAmount;
        auto it = upper_bound(mx_bid[itemId].begin(), mx_bid[itemId].end(), make_pair(newAmount, userId));
        mx_bid[itemId].insert(it, {newAmount, userId});
    }
    
    void removeBid(int userId, int itemId) {
        bids.erase({userId, itemId});
    }
    
    int getHighestBidder(int itemId) {
        auto &v = mx_bid[itemId];
        while (!v.empty() && (!bids.count({v.back().second, itemId}) ||
                bids[{v.back().second, itemId}]!=v.back().first)) {
            mx_bid[itemId].pop_back();
        }

        return v.empty()?-1:v.back().second;
    }
};

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */