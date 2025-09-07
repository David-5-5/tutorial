#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.4 组合型回溯
class CombinationIterator {
private:
    string characters;
    int combinationLength;
    vector<string> combinations;
    int currentIndex;
    
    // 生成所有组合的辅助函数
    void generateCombinations(int start, int length, string& current) {
        if (length == 0) {
            combinations.push_back(current);
            return;
        }
        
        for (int i = start; i <= characters.size() - length; ++i) {
            current.push_back(characters[i]);
            generateCombinations(i + 1, length - 1, current);
            current.pop_back();
        }
    }
    
public:
    CombinationIterator(string characters, int combinationLength) {
        this->characters = characters;
        this->combinationLength = combinationLength;
        this->currentIndex = 0;
        
        // 预生成所有组合
        string current;
        generateCombinations(0, combinationLength, current);
    }
    
    string next() {
        return combinations[currentIndex++];
    }
    
    bool hasNext() {
        return currentIndex < combinations.size();
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */