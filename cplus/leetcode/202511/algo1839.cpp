#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        // 自行解答 - 太复杂
        string towel = "aeiou"; int exp = 0, cnt = 0, ans = 0, cur = 0;

        for (auto& ch : word) {
            if (ch == towel[exp]) cnt ++;
            else if (cnt && ch == towel[(exp+1)%5]) {
                exp = (exp+1)%5; exp==0?cur=0:cur+=cnt; cnt = 1; 
            } else cur = 0, cnt = (ch=='a'?1:0), exp = 0;
            
            if (exp == 4 && cnt) ans = max(ans, cur + cnt);
        }
        return ans; 
    }

};

int main() {
    cout << Solution().longestBeautifulSubstring("aiaeioouaaeeiouuiuieeo") << endl;
}