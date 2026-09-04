#include <bits/stdc++.h>
using namespace std;

class Spreadsheet {
private:
    vector<vector<int>> cells;
public:
    Spreadsheet(int rows) : cells(26, vector<int>(rows)) {
    }
    
    void setCell(string cell, int value) {
        cells[cell[0]-'A'][stoi(cell.substr(1))-1] = value;
    }
    
    void resetCell(string cell) {
        cells[cell[0]-'A'][stoi(cell.substr(1))-1] = 0;
    }
    
    int getValue(string formula) {
        size_t p = formula.find('+');
        string c1 = formula.substr(1, p), c2 = formula.substr(p+1);
        int ans = 0;
        if (c1[0] >= 'A' && c1[0] <= 'Z') {
            ans += cells[c1[0]-'A'][stoi(c1.substr(1))-1];
        } else ans += stoi(c1);
        if (c2[0] >= 'A' && c2[0] <= 'Z') {
            ans += cells[c2[0]-'A'][stoi(c2.substr(1))-1];
        } else ans += stoi(c2);

        
        return ans;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */