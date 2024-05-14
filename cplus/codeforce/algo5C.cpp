#include <bits/stdc++.h>
using namespace std;

int instack(string input)
{
    stack<int> stk;
    stk.push(-1);
    int longest = 0;
    int count = 1;

    int n = input.length();
    for (int i = 0; i < n; i++)
    {
        if (input[i] == '(')
        {
            stk.push(i);
        }
        else
        {
            stk.pop();
            if (stk.empty())
            {
                stk.push(i);
            }
            else
            {
                if (i - stk.top() > longest)
                {
                    longest = i - stk.top();
                    count = 1;
                }
                else if (i - stk.top() == longest)
                {
                    count++;
                }
            }
        }
    }

    cout << longest << " " << count << endl;
    return 0;
}

int indp(string input)
{
    int n = input.length();
    int dp[n];
    int longest = 0;
    int count = 1;

    dp[0]= 0;
    for (int i = 1; i < n; i++)
    {   
        dp[i] = 0;
        if (input[i] == ')')
        {
            if (input[i - 1] == '(')
            {
                dp[i] = 2;
                if (i > 1)
                {
                    dp[i] += dp[i - 2];
                }
            }
            else
            {
                if (dp[i - 1] > 0 && i - dp[i - 1] > 0 && input[i - dp[i - 1] - 1] == '(')
                {
                    dp[i] = dp[i - 1] + 2;
                    if (i - dp[i - 1] - 1 > 0)
                    {
                        dp[i] += dp[i - dp[i - 1] - 2];
                    }
                }
            }

            if (dp[i] > longest) {
                longest = dp[i];
                count = 1;
            } else if (dp[i] > 0 && dp[i] == longest) {
                count ++;
            }
        }
    }

    cout << longest << " " << count << endl;
    return 0;
}

int main()
{
    string input;
    cin >> input;

    indp(input);
}