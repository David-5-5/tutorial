#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        set<string> words(wordlist.begin(), wordlist.end());
        set<char> vowel_list = {'a', 'e', 'i', 'o', 'u'};

        unordered_map<string, string> wilds, vowels;
        auto to_lower = [&](string ori) -> string {
            string res = ori;
            transform(res.begin(), res.end(), res.begin(), ::tolower);
            return res;
        };
        
        auto rep_vowel = [&](string ori) -> string {
            string res = ori;
            for (int i=0; i<res.length(); i++) {
                if (vowel_list.count(res[i])) res[i] = '*';
            }
            return res;
        };

        for (auto & word: wordlist) {
            auto low = to_lower(word);
            if (!wilds.count(low)) wilds[low] = word;

            auto match = rep_vowel(low);
            if (!vowels.count(match)) vowels[match] = word;
        }

        vector<string> ans;
        for (auto& q: queries) {
            if (words.count(q)) {
                ans.emplace_back(q); continue;
            }
            auto low = to_lower(q);
            if (wilds.count(low)) {
                ans.emplace_back(wilds[low]); continue;
            }
            auto match = rep_vowel(low);
            if (vowels.count(match)) {
                ans.emplace_back(vowels[match]); continue;
            }
            ans.emplace_back("");
        }

        return ans;
    }
};