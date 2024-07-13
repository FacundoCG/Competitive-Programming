#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second

ll minimo(vector<ll>& res, vector<ll>& vec, ll l){
    ll min = 0;
    for(ll i=1; i<l; i++){
        if(vec[res[i]] < vec[res[min]]){
            min = i;
        } else if(vec[res[i]] == vec[res[min]]){
            if(res[i] > res[min]){
                min = i;
            }
        }
    }
    return min;
}

vector<ll> subsecuenciaMasCorta(vector<ll>& vec, ll n, ll l){
    vector<ll> res;
    for(ll i=0; i<n; i++){
        res.push_back(i);
    }
    
    for(ll i=n; i < l; i++){
        ll min = minimo(res, vec, n);
        if(vec[i] > vec[res[min]]){
            res[min] = i;
        }
    }
    sort(res.begin(), res.end());
    for(ll i=0; i<n; i++){
        res[i] = vec[res[i]];
    }
    return res;

}

int main()
{
    // Lectura inputs:
    long long n, k, val, a, b;

    cin >> n;
    vector<ll> vec;
    for(ll i=0; i<n; i++){
        cin >> val;
        vec.push_back(val);
    }

    cin >> k;
    
    for(ll i=0; i<k; i++){
        cin >> a >> b; // a is the length of the subsequence and b is the position that you are intersted
        vector<ll> res = subsecuenciaMasCorta(vec, a, n);
        ll h = res[b-1];
        cout << h << "\n";
    }
}