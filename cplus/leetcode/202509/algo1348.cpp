#include <bits/stdc++.h>
using namespace std;

// 有序集合 - 自行解答
class TweetCounts {
private:
    unordered_map<string, multiset<int>> tweets;
public:
    TweetCounts() {}
    
    void recordTweet(string tweetName, int time) {
        tweets[tweetName].insert(time);
    }
    
    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        int intervals = 60; vector<int> ans;
        if (freq == "hour") intervals *= 60;
        else if (freq == "day") intervals *= 60 * 24;
        
        int left = startTime;
        while (left <= endTime) {
            int right = min(left + intervals-1, endTime);
            ans.push_back(distance(tweets[tweetName].lower_bound(left),
                tweets[tweetName].upper_bound(right)));
            left += intervals;
        }
        return ans;
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */