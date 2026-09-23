#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
private:
    // 前缀的乘积，特殊处理值为 0
    vector<int> prod;
    int last = -1;
public:
    ProductOfNumbers() {
        prod.emplace_back(1);
    }
    
    void add(int num) {
        if (num == 0) {
            last = prod.size();
            prod.emplace_back(1);
        } else prod.emplace_back(prod.back() * num);
    }
    
    int getProduct(int k) {
        int n = prod.size();
        if (last >= n-k) return 0;
        return prod.back() / prod[n-1-k];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */