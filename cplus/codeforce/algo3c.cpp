#include <bits/stdc++.h>
using namespace std;

char ttt[3][3];
string lines[8];

// return 0, if count(X) == count(0)
// return 1, if count(X) == count(0) + 1
// return -1, illege
// return 3, if count(X) = 5, count(0) = 4
int count()
{
    int cnt_x = 0, cnt_0 = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (ttt[i][j] == 'X')
                cnt_x++;
            else if (ttt[i][j] == '0')
                cnt_0++;
        }

    if (cnt_x == 5 && cnt_0 == 4)
        return 3;
    if (cnt_x == cnt_0)
        return 0;
    if (cnt_x == cnt_0 + 1)
        return 1;
    return -1;
}

// return 0, if X is three
// return 1, if O is three
// return 3, need continue
// retrurn -1, if X + O is more than 1
int match()
{
    // int conti = 8;
    int mth_x = 0, mth_0 = 0;

    // for each row
    for (int i = 0; i < 8; i++)
    {
        if (lines[i] == "XXX")
        {
            mth_x++;
        }
        else if (lines[i] == "000")
        {
            mth_0++;
        }

    }

    if (mth_x == 0 && mth_0 == 0)
    {
        return 3;
    }
    if (mth_x > 0 && mth_0 == 0)
        return 0;
    if (mth_x == 0 && mth_0 > 0)
        return 1;

    return -1;
}

int main()
{
    for (int i = 0; i < 3; i++)
    {
        string input;
        cin >> input;
        ttt[i][0] = input[0];
        ttt[i][1] = input[1];
        ttt[i][2] = input[2];
        lines[i] = input;
    }

    lines[3].append(1, ttt[0][0]).append(1, ttt[1][0]).append(1, ttt[2][0]);
    lines[4].append(1, ttt[0][1]).append(1, ttt[1][1]).append(1, ttt[2][1]);
    lines[5].append(1, ttt[0][2]).append(1, ttt[1][2]).append(1, ttt[2][2]);

    lines[6].append(1, ttt[0][0]).append(1, ttt[1][1]).append(1, ttt[2][2]);
    lines[7].append(1, ttt[0][2]).append(1, ttt[1][1]).append(1, ttt[2][0]);

    int count_ttt = count();
    int match_ttt = match();
    if (count_ttt == -1 || match_ttt == -1)
    {
        cout << "illegal" << endl;
        return 0;
    }

    if (match_ttt == 0 && count_ttt >= 1)
    {
        cout << "the first player won" << endl;
    }
    else if (match_ttt == 1 && count_ttt == 0)
    {
        cout << "the second player won" << endl;
    }
    else if (match_ttt == 3)
    {
        if (count_ttt == 0)
        {
            cout << "first" << endl;
        }
        else if (count_ttt == 1)
        {
            cout << "second" << endl;
        }
        else
        {
            cout << "draw" << endl;
        }
    }
    else
    {
        cout << "illegal" << endl;
    }

    return 0;
}
