#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;


int main()
{
    int A,B,C;
    cin >> A >> B >> C;

    map<int,int> dict;
    string res = "N";

    if (A >= B+C || B >= A+C || C >= A+B){
        res = "S";
    }

    cout << res << "\n";
}
