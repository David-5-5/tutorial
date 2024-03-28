#include <iostream>
#include <vector>

using namespace std;

string solution(vector<int> bars){
    long sum = bars.size();

    // Caculate the prefix sum
    vector<int> presum(sum+1);
    for (int i=0; i<sum;i++) {
        presum[i+1] = presum[i] + bars[i];
    }

    long left = 1;
    // when sum[0..left-1] <= sum[left+1..n]
    while (left < sum  && presum[left] <= presum[sum]-presum[left+1] ) {
        left ++;
    }

    return to_string(left) + ' ' + to_string(sum-left);
}

int main()
{
    int total;
    cin >> total;
    vector<int> bars;
    for (int i = 0; i < total; i++) {
        int time;
        cin >> time;
        bars.emplace_back(time);
    }
    cout << solution(bars) << endl;
}