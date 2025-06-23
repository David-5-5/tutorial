#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Twitter {
private:
    int time = 1;
    unordered_map<int, int> time_twid;
    unordered_map<int, vector<int>> tweets;
    unordered_map<int, set<int>> follows;
public:
    Twitter() {
    }
    
    void postTweet(int userId, int tweetId) {
        time_twid[time] = tweetId;
        tweets[userId].push_back(time++);
    }
    
    vector<int> getNewsFeed(int userId) {
        int news_count = 0;
        vector<int> result;
        priority_queue<tuple<int, int, int>> recent;
        if (tweets[userId].size()) {
            int inx = tweets[userId].size() - 1;
            recent.emplace(tweets[userId][inx], userId, inx);
        }
        for (auto it = follows[userId].begin(); it!=follows[userId].end(); ++it) {
            if (tweets[*it].size()) {
                int inx = tweets[*it].size() - 1;
                recent.emplace(tweets[*it][inx], *it, inx);
            }            
        }

        while (recent.size() && result.size()<10) {
            auto [t, u, i] = recent.top();
            result.push_back(time_twid[t]);
            recent.pop();
            if (i) recent.emplace(tweets[u][i-1], u, i-1);
        }

        return result;
    }
    
    void follow(int followerId, int followeeId) {
        follows[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        follows[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */