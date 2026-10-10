#include <bits/stdc++.h>
using namespace std;

class AuthenticationManager {
private:
    int timeToLive;
    unordered_map<string, int> alives;
public:
    AuthenticationManager(int timeToLive): timeToLive(timeToLive) {
    }
    
    void generate(string tokenId, int currentTime) {
        alives[tokenId] = currentTime + timeToLive;
    }
    
    void renew(string tokenId, int currentTime) {
        if (alives.count(tokenId) && alives[tokenId] > currentTime) {
            alives[tokenId] = currentTime + timeToLive;
        }
    }
    
    int countUnexpiredTokens(int currentTime) {
        int cnt = 0;
        for (auto &[k, v] :alives) {
            if (v > currentTime) cnt ++;
        }
        return cnt;
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */