#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
 
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ld EPSILON = 1e-10;
 
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.


int main()
{
	ll n, d;
	
	cin >> n >> d;
	
	vector<ll> hoteles(n);
	
	for(ll i=0; i<n; i++){
		cin >> hoteles[i];
	}
	
	ll res = 2;
	
	for(ll i=0; i<n-1; i++){
		if (hoteles[i+1] - hoteles[i] == 2*d){
			res += 1;
		}
		if (hoteles[i+1] - hoteles[i] > 2*d){
			res += 2;
		}
	}
	
	cout << res;
	
    return 0;
}
