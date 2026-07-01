#include <bits/stdc++.h>
using namespace std;

class WordsFrequency {
private:
    unordered_map<string, int> freq;
public:
    WordsFrequency(vector<string>& book) {
        for (auto w:book) freq[w] ++;
    }
    
    int get(string word) {
        return freq[word];
    }
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */