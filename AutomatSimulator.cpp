#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct rule
{
    int old_st;
    char symbol;
    int new_st;
};
vector<char> a;
vector<int> s;
vector<int> f;
vector<rule> r;
bool reachable[101] = { 0 };
bool rev_reach[101][101] = { 0 };
void reset()
{
    for (int i = 0; i < s.size(); ++i) reachable[i] = false;
}
void w1_search(string w1, int cur_st, int finish_st, string& res)
{
    reachable[cur_st] = true;
    if (cur_st == finish_st)
    {
        res = w1;
        return;
    }
    for (int i = 0; i < r.size(); ++i)
    {
        if ((r[i].old_st == cur_st) && (!reachable[r[i].new_st])) w1_search(w1 + r[i].symbol, r[i].new_st, finish_st, res);
    }
    return;
}
int main()
{
    int A, S, S0, F, R, st, st_new, cur_st, temp;
    char C;
    rule r0;
    string w0, w1, res;
    bool correct = true;
    cin >> A;
    C = 97;
    for (int i = 0; i < A; ++i)
    {
        a.push_back(C);
        ++C;
    }
    cin >> S;
    for (int i = 0; i < S; ++i) s.push_back(i);
    cin >> S0 >> F;
    for (int i = 0; i < F; ++i)
    {
        cin >> st;
        f.push_back(st);
    }
    cin >> R;
    for (int i = 0; i < R; ++i)
    {
        cin >> st >> C >> st_new;
        r0.old_st = st;
        r0.symbol = C;
        r0.new_st = st_new;
        r.push_back(r0);
    }
    cin >> w0;
    int L = w0.size();
    vector<int> st_q[101];
    bool check = true;
    for (int i = 0; i < F; ++i)
    {
        st_q[0].push_back(f[i]);
        rev_reach[0][f[i]] = true;
    }
    for (int i = 0; i < L; ++i)
    {
        for (int j = 0; j < st_q[i].size(); ++j)
        {
            for (int k = 0; k < R; ++k)
            {
                if ((r[k].new_st == st_q[i][j]) && (r[k].symbol == w0[L - 1 - i]) && (!rev_reach[i + 1][r[k].old_st]))
                {
                    rev_reach[i + 1][r[k].old_st] = true;
                    st_q[i + 1].push_back(r[k].old_st);
                }
            }
        }
    }
    for (int i = 0; i <= L; ++i)
    {
        if (!st_q[i].size())
        {
            check = false;
            break;
        }
    }
    if (check)
    {
        check = false;
        for (int i = 0; i < st_q[L].size(); ++i)
        {
            reset();
            w1 = "";
            w1_search(w1, S0, st_q[L][i], res);
            if (reachable[st_q[L][i]])
            {
                check = true;
                break;
            }
        }
    }
    if (check) cout << res;
    else cout << "There is no such word w1 that w1w0 is readable by the automat";
    return 0;
}
