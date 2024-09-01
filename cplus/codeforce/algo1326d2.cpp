#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <time.h>
#include <math.h>

using namespace std;

string solution(string s)
{
    int n = s.length();
    vector<int> d1(n), d2(n);
    
    // !!!!!!!!!!!!!!RESERVED FOR COMPARING!!!!!!!!!
    //
    // int l = 0, r = -1;
    // for (int i=0; i<n; i++) {
    //     if (i <= r)
    //         d1[i] = min(d1[l+r-i], r-i);
    //     while (0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]])
    //         d1[i] += 1;
    //     if (i + d1[i] > r)
    //         l, r = i - d1[i], i + d1[i];
    // }

    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            // Bad performance
            // l,r  = i - k, i + k;
            // Good performance
            l = i- k, r = i + k;
            // r = i + k;
        }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
        {
            k++;
        }
        d2[i] = k--;
        if (i + k > r)
        {
            l = i - k - 1;
            r = i + k;
        }
    }

    function<string(string, int, int)> find = [&](string s, int l, int r)
    {
        if (l == r)
            return s.substr(l, 1);
        if (l > r)
            return s.substr(l, 0);

        int mid = l + (r - l + 1) / 2, rem = (r - l + 1) % 2;
        if ((rem == 0 and d2[mid] + mid == r + 1) or (rem == 1 and d1[mid] + mid == r + 1))
            return s.substr(l, r + 1 - l);

        int lmax = 1;
        for (int i = l + 1; i <= mid; i++)
        {
            if (i - d2[i] <= l)
                lmax = max(lmax, (i - l) * 2);
            if (i + 1 - d1[i] <= l and i < mid)
                lmax = max(lmax, (i - l + 1) * 2 - 1);
        }
        int rmax = 1;
        for (int i = r; i >= mid; i--)
        {
            if (i > mid and i - 1 + d2[i] >= r)
                rmax = max(rmax, (r - i + 1) * 2);
            if (i - 1 + d1[i] >= r)
                rmax = max(rmax, (r - i + 1) * 2 - 1);
        }
        string midstr = "";
        int count = 0;
        while (s[l + count] == s[r - count])
            count += 1;
        if (count > 0)
            midstr = s.substr(l, count) + find(s, l + count, r - count) + s.substr(r - count + 1, count);

        int midlen = midstr.length();
        int maxf = max(max(lmax, rmax), midlen);
        if (maxf == lmax)
            return s.substr(l, lmax);
        else if (maxf == rmax)
            return s.substr(r - rmax + 1, rmax);
        else
            return midstr;
    };
    return find(s, 0, n - 1);
}

int main()
{
    int total;
    cin >> total;
    for (int i = 0; i < total; i++)
    {
        string input;
        cin >> input;
        cout << solution(input) << endl;
    }

    // Unit test
    // cout << solution("abcdfdcecba") << endl;
    // cout << solution("abbaxyzyx") << endl;
    // cout << solution("codeforces") << endl;
    
    // Benchmark
    // clock_t start = clock();
    // string s = "";
    // s.append(1000, 'x');
    // int loop = pow(10, 7) / s.length();
    // for (int i = 0; i < loop ; i++){
    //     solution(s);
    // }
    // cout<<"time = "<<double(clock()-start)/CLOCKS_PER_SEC<<"s"<<endl;
}