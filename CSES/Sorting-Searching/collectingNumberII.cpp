#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
const ld EPSILON = 1e-10;
const double PI = acos(-1.0);

#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

// Show vector
template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

// Show set
template <typename T>
ostream & operator <<(ostream &os, const set<T> &s) {
    os << "{";
    for(auto it = s.begin(); it != s.end(); it++){
        if(it != s.begin()) os << ",";
        os << *it;
    }
    return os << "}";
}

// ############################################################### //

int f(vector<int> &A, int index1, int index2){
	int res = 0;
	
	if (index1 == index2){
		if (0 <= index1-1) res += (A[index1] < A[index1-1]);
		if (index1+1 < SIZE(A)) res += (A[index1+1] < A[index1]);
	} else if (index1 + 1 == index2){
		res += (A[index2] < A[index1]);
		if (0 <= index1-1) res += (A[index1] < A[index1-1]);
		if (index2+1 < SIZE(A)) res += (A[index2+1] < A[index2]);
	} else if (index2 + 1 == index1){
		res += (A[index1] < A[index2]);
		if (0 <= index2-1) res += (A[index2] < A[index2-1]);
		if (index1+1 < SIZE(A)) res += (A[index1+1] < A[index1]);
	} else {
		if (0 <= index1-1) res += (A[index1] < A[index1-1]);
		if (index1+1 < SIZE(A)) res += (A[index1+1] < A[index1]);
		if (0 <= index2-1) res += (A[index2] < A[index2-1]);
		if (index2+1 < SIZE(A)) res += (A[index2+1] < A[index2]);
	}
	
	
	return res;
}

void swap(vector<int> &C, int i, int j){
	int oldValue = C[i];
	C[i] = C[j];
	C[j] = oldValue;
}

int main()
{
	ll n, m;
	cin >> n >> m;

	vector<int> A(n), B(n);	
	
	forn(i, n){
		int k;
		cin >> k;
		B[i] = k;
		A[k-1] = i;
	}
	
	int res = 1;
	
	forsn(i, 1, n){
		if (A[i] < A[i-1]) res++; 
	}
	
	//~ DBG(res);
	
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		
		//~ DBG(B); DBG(A);
		//~ DBG(a); DBG(b);
		
		int j1 = B[a], j2 = B[b];
		swap(B, a, b);
		//A[j1-1] = a, A[j2-1] = b;
		
		res = res - f(A, j1-1, j2-1);
		swap(A, j1-1, j2-1);
		//~ DBG(B); DBG(A);
		//~ DBG(j1-1); DBG(j2-1);
		res = res + f(A, j1-1, j2-1);
		
		//int j2 = B[a], j1 = B[b];
		//A[j2-1] = a, A[j1-1] = b;
		
		cout << res << "\n";
	}
	
	
    return 0;
}
