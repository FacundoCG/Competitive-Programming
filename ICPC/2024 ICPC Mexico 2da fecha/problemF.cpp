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



int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);

	int n, p;
	cin >> n >> p;
	
	vi A(n);
	forn(i, n) cin >> A[i];
	sort(all(A));
	ll res = 0;
	
	forn(i, n){ if (A[i] <= p) res = A[i];}
	
	cout << res << "\n";
	

    return 0;
}
