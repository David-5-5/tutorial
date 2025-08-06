#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.2 树状数组和线段树 - 逆序对
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}
    // a[i] 增加 val, 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    // 求前缀和 a[1] + ... + a[i] 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res += tree[i];
        }
        return res;
    }
    // 求区间和 a[l] + ... + a[r], 1 <= l <= r <= n
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

class Solution {
public:
    int getMinSwaps(string num, int k) {
        // 先求出第 k 大的排列，树状数组求逆序对的方法
        string num_k = num;
        while(k--) {
            next_permutation(num_k.begin(), num_k.end());
        }

        int n = num.size();
        FenwickTree<int> ft(n);
        // pos[i] 存储数字 i 在 num 中的下标列表
        vector<int> pos[10];
        for (int i = 0; i < n; ++i) {
            pos[num[i]-'0'].push_back(i);
        }
        
        vector<int> seq; // num_k 按照 num 的顺序
        for (int i=n-1; i>=0; --i) {
            seq.push_back(pos[num_k[i]-'0'].back());
            pos[num_k[i]-'0'].pop_back();
        }
        reverse(seq.begin(), seq.end());

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += ft.query(seq[i]+2, n);
            ft.update(seq[i] + 1, 1);
        }
        return ans;
    }


    int getMinSwaps2(string num, int k) {
        string num_k = num;
        while(k--) {
            next_permutation(num_k.begin(), num_k.end());
        }

        int n = num.size(), ans = 0;

        for (int i = 0; i < n; ++i) {
            if (num[i] == num_k[i]) continue;
            for (int j=i+1; j<n; ++j){
                if (num[j] == num_k[i]) {
                    for (int k=j-1; k>=i; --k) {
                        swap(num[k], num[k+1]);
                    }
                    ans += j-i;
                    break;
                }
            }
        }
        return ans;
    }
};

int getMinSwaps2(string num, string shuffle) {

    int n = num.size();
    FenwickTree<int> ft(n);
    // pos[i] 存储数字 i 在 num 中的下标列表
    vector<int> pos[10];
    for (int i = 0; i < n; ++i) {
        pos[num[i]-'0'].push_back(i);
    }
    
    vector<int> seq; // num_k 按照 num 的顺序
    for (int i=n-1; i>=0; --i) {
        seq.push_back(pos[shuffle[i]-'0'].back());
        pos[shuffle[i]-'0'].pop_back();
    }
    reverse(seq.begin(), seq.end());

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += ft.query(seq[i]+2, n);
        ft.update(seq[i] + 1, 1);
    }
    return ans;
}


int getMinSwaps(string num, string shuffle) {

    int n = num.size(), ans = 0;

    for (int i = 0; i < n; ++i) {
        if (num[i] == shuffle[i]) continue;
        for (int j=i+1; j<n; ++j){
            if (num[j] == shuffle[i]) {
                for (int k=j-1; k>=i; --k) {
                    swap(num[k], num[k+1]);
                }
                ans += j-i;
                break;
            }
        }
    }
    return ans;
}

string generateTestString(int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist('0', '9');  // 生成'0'到'9'的ASCII码
    
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s += static_cast<char>(dist(gen));
    }
    return s;
}


std::string shuffleString(const std::string& s) {
    // 复制原字符串以避免修改输入
    std::string shuffled = s;
    
    // 使用当前时间作为随机种子，确保每次结果不同
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    // 打乱字符串
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937(seed));
    
    return shuffled;
}


int main() {
    // 测试配置（可修改字符串长度）
    const int strLength = 100000;  // 字符串长度
    // 生成测试数据（仅含0-9的数字字符串）
    string testStr = generateTestString(strLength);
    string shuffle = shuffleString(testStr);
    // 测试 getMinSwaps
    auto start1 = chrono::high_resolution_clock::now();
    int result1 = getMinSwaps2(testStr, shuffle);
    auto end1 = chrono::high_resolution_clock::now();
    double time1 = chrono::duration<double, milli>(end1 - start1).count();
    // cout << testStr << endl;
    // 测试 getMinSwaps2
    auto start2 = chrono::high_resolution_clock::now();
    int result2 = getMinSwaps(testStr, shuffle);
    auto end2 = chrono::high_resolution_clock::now();
    double time2 = chrono::duration<double, milli>(end2 - start2).count();
    
    // 输出结果
    cout << "测试字符串长度: " << strLength << " 个字符（仅含0-9）\n";
    cout << "getMinSwaps 执行时间: " << time1 << " 毫秒, 结果: " << result1 << "\n";
    cout << "getMinSwaps2 执行时间: " << time2 << " 毫秒, 结果: " << result2 << "\n";
    cout << "性能提升: " << (time1 / time2) << " 倍\n";
    
    return 0;
}
