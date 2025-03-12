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
	ll n;
	
	ll a_x, a_y;
	ll b_x, b_y;
	ll c_x, c_y;
	
	cin >> n;
	cin >> a_x >> a_y;
	cin >> b_x >> b_y;
	cin >> c_x >> c_y;
	
	if (b_x <= a_x && a_x <= c_x){
		cout << "NO";
		return 0;
	}
	
	if (c_x <= a_x && a_x <= b_x){
		cout << "NO";
		return 0;
	}
	
	if (b_y <= a_y && a_y <= c_y){
		cout << "NO";
		return 0;
	}
	
	if (c_y <= a_y && a_y <= b_y){
		cout << "NO";
		return 0;
	}
	
	cout << "YES";
	
    return 0;
}
