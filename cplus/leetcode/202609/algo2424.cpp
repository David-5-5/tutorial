#include <bits/stdc++.h>
using namespace std;

class LUPrefix {
private:
    vector<int> uploads;
    int x = 0;
public:
    LUPrefix(int n):uploads(n+1) {
        uploads[0] = 1;
    }
    
    void upload(int video) {
        uploads[video] = 1;
        if (x + 1 == video) {
            x += 1;
            while (x+1 < uploads.size()  && uploads[x+1]) x+=1;
        }
    }
    
    int longest() {
        return x;
    }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */