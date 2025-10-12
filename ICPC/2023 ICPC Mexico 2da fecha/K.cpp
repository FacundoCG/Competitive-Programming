#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vvi = vector<vi>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;

#define pb push_back
#define fst first
#define snd second

#define esta(x, c) ((c).find(x) != (c).end())
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << "=" << (x) << endl;
#define RAYA cerr << "-----------" << endl;

#define forn(i, n) for(int i=0; i<(int)(n);i++)
#define forsn(i, s, n) for(int i=(s); i<(int)(n);i++)

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
	os << "[";
	forn(i, SIZE(v)){
		if (i > 0) os << ",";
		os << v[i];
	}
	return os << "]";
}

// ######################## //

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vvi mat(n, vi(n));
	
	forn(i, n){
		forn(j, n){
			cin >> mat[i][j];
		}
	}
	
	int res = 0;
	
	forn(i, n){
		forn(j, n){
			if(i+k-1<n && j+k-1<n){
				int val = mat[i][j];
				if(val == mat[i+k-1][j] && val == mat[i][j+k-1] && val == mat[i+k-1][j+k-1]){
					res++;
				}
			}
		}
	}
	
	cout << res << "\n";
	
	return 0;
}
