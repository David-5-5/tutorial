#include <bits/stdc++.h>
using namespace std;

int main() {
    // print matrix
    vector<vector<int>> matrix = {{1,2},{3,4}};

    for (auto& r:matrix) {
        for (auto& v:r) cout << v << ",";
        cout << endl;
    }

    vector<int> arr = {1,2,3,4};
    for (auto& v:arr) cout << v << ",";
    cout << endl;
}
