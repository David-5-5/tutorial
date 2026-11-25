#include <bits/stdc++.h>
using namespace std;


class Solution {
private:
    unordered_map<string, string> entity = {{"quot", "\""}, {"apos", "'"}, {"amp", "&"}, {"gt", ">"}, {"lt", "<"}, {"frasl", "/"}};
public:
    string entityParser(string text) {
        char begin = '&', end = ';';

        string ans, key; bool in_key = false;

        for (auto ch : text) {

            if (in_key) {
                if (ch == begin) {
                    ans += begin + key;
                    key = "";
                } else if (ch == end) {
                    if (entity.contains(key)) ans += entity[key];
                    else ans += begin + key + end;
                    in_key = false;
                } else key += ch;
            } else {
                if (ch == begin) {key = ""; in_key = true;}
                else ans += ch;
            }
        }
        return ans + (in_key?begin+key:"");
    }
};