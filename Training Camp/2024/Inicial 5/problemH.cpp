#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
#define pb push_back

// ############################################################### //


int main()
{
    // Lectura inputs:
    ll t;
    string s;

    cin >> t;

    for(ll i_t=0; i_t<t; i_t++){
        cin >> s;

        if (s[0] != s[s.size()-1]){
            s[s.size()-1] = s[0];
        }

        cout << s << "\n";
    }

    return 0;
}
