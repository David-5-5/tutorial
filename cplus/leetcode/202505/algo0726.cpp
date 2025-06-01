#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    string countOfAtoms(string formula) {
        // 自行解答
        vector<map<string, int>> st(1);

        formula += "&"; // 添加哨兵

        string atom = "";
        int pos = -1, n = formula.length(), pop = 0;

        for (int i=0; i<n; ++i) {
            char ch = formula[i];

            // 元素入栈
            if ((ch >='A' && ch<='Z') || ch == '(' || ch == ')' || ch == '&') {
                if (pop) {
                    int cnt = i-pos>1?stoi(formula.substr(pos+1, i-pos-1)):1;
                    map<string, int> sub = st.back();
                    st.pop_back();
                    for (auto& [k, v]: sub) {
                        st.back()[k] += v * cnt;
                    }
                    pop ^= 1;
                } else if (atom.length()) {
                    if (i-pos == 1) st.back()[atom] += 1;
                    else st.back()[atom] += stoi(formula.substr(pos+1, i-pos-1));
                    atom = "";
                }
                pos = i;
            }

            if (ch >= 'A' && ch <= 'Z') {
                atom = ch;
            } else if (ch >= 'a' && ch <= 'z') atom += ch, pos = i;
            else if (ch == '(') st.emplace_back();  // 栈中增加元素
            else if (ch == ')') pop = 1;

        }

        string ans = "";
        for (auto& [k, v] : st[0]) {
            // cout << k << "," << v << endl;
            ans += k + (v>1?to_string(v):"");
        }
        return ans; 

    }
};

int main() {
    cout << Solution().countOfAtoms("((HHe28Be26He)9)34") << endl;
}