#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        int block = false; string statement;

        vector<string> ans;
        for (auto  line: source) {
            int i = 0;
            while (i < line.size()) {
                if (block) {
                    if (i+1 < line.size() && line[i] == '*' && line[i+1] == '/') {
                        block = false;
                        i += 2;
                    } else i++;
                } else {
                    if (i + 1 < line.size() && line[i] == '/' && line[i+1] == '/')  {
                        if (statement.length()) {
                            ans.emplace_back(statement); statement = "";
                        } break; // next line
                    } else if (i+1 < line.size() && line[i] == '/' && line[i+1] == '*') {
                        i += 2; block = true;
                    } else {
                        statement += line[i++];
                    }
                }
            }
            if (!block && statement.length()) {
                ans.emplace_back(statement); statement = "";
            }
        }
        return ans;
    }
};