#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 逆向思维
class Encrypter {
private:
    unordered_map<char, string> kv;
    vector<string> dict;
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        for (int i=0; i<keys.size(); i++)
            kv[keys[i]] = values[i];
        
        dict = dictionary;
    }
    
    string encrypt(string word1) {
        string ans = "";
        for (auto ch : word1) {
            if (!kv.count(ch)) return "";   // 边界
            ans += kv[ch];
        }
        return ans;
    }
    
    // 不需要执行解密操作，仅将 dict 中字符串进行进行加密操作，是否等于 word2
    int decrypt(string word2) {
        int ans = 0;               
        for (auto w:dict) {
            ans += (word2 == encrypt(w));
        }
        return ans;
    }
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */