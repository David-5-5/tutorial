#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 回文串贪心

class Solution {
public:
    string nearestPalindromic(string n) {
        // 使用 deepseek 从 python 翻译过来
        long num = stol(n);
        if (num <= 10) return to_string(num - 1);
        if (num == 11) return "9";
        
        // Generate all possible candidates
        set<long> candidates;
        
        // Handle special cases: 10...0 becomes 9...9
        candidates.insert((long)pow(10, n.length()) + 1);
        candidates.insert((long)pow(10, n.length() - 1) - 1);
        
        // Get the first half
        string half = n.substr(0, (n.length() + 1) / 2);
        
        // Generate candidates by mirroring
        for (int delta = -1; delta <= 1; delta++) {
            string newHalf = to_string(stol(half) + delta);
            string candidate;
            if (n.length() % 2 == 0) {
                candidate = newHalf + string(newHalf.rbegin(), newHalf.rend());
            } else {
                candidate = newHalf + string(newHalf.rbegin() + 1, newHalf.rend());
            }
            candidates.insert(stol(candidate));
        }
        
        // Remove the original number if it's a palindrome
        bool isPalindrome = true;
        for (int i = 0; i < n.length() / 2; i++) {
            if (n[i] != n[n.length() - 1 - i]) {
                isPalindrome = false;
                break;
            }
        }
        if (isPalindrome) {
            candidates.erase(num);
        }
        
        // Find the closest candidate
        long minDiff = LONG_MAX;
        long result = 0;
        for (long candidate : candidates) {
            long diff = abs(candidate - num);
            if (diff < minDiff) {
                minDiff = diff;
                result = candidate;
            } else if (diff == minDiff && candidate < result) {
                result = candidate;
            }
        }
        
        return to_string(result);        
    }
};