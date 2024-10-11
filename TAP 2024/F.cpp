#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
const ld EPSILON = 1e-10;


int main()
{
    ll n;
    ll racha = 0;
    ll res = 0;
    cin >> n;

    vector<ll> partidos(n);

    for(ll i=0; i<n; i++){
        cin >> partidos[i];
    }

    for(ll i=0; i<n; i++){
        if(partidos[i] == 1){
            res++;
            racha++;
            if(racha >= 3){
                res++;
            }
        } else {  // Perdio el partido
            res--;
            racha = 0;
        }
    }

    cout << res;

}
