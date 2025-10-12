#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;

using vi = vector<int>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define SIZE(c) int((c).size())


#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "------------------" << endl

#define forn(i, n) for (int i=0;i<(int)(n); i++)
#define forsn(i, s, n) for (int i=(s);i<(int)(n); i++)

// Show vector

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
    os << "[";
    forn(i, v.size()){
        if(i>0) os << ",";
        os << v[i];
    }
    return os << "]";
}

vi divisoresOf(int a){
	vi res;
	int until = (int) sqrt(a) + 1;
	forsn(i, 1, until){
		if (a % i == 0) res.pb(i);
		if (a % i == 0 && i != a/i) res.pb(a/i);
	}
	
	return res;
}


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);

	int q;
	cin >> q;
	
	forn(_, q){
		int n, t;
		cin >> n >> t;
		int res = 0;
		
		t -= 1;
		
		if (t == 0) res = n;
		else {
			vi divisoresT = divisoresOf(t);
			for (int d : divisoresT){
				if (d <= n) res ++;
			}
		}
		
		cout << res << "\n";
	}
	

    return 0;
}
