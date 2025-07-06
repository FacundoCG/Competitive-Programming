#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vl = vector<ll>;
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

struct SqrtDescomposition{
    vl A;
    vector<vl> descompositionOfA;
    vl sumOfDescomposition;
    int n, sqrtOfN;

    SqrtDescomposition(vl &arr) : A(arr){
        n = SIZE(arr);
        sqrtOfN = (int) sqrt(n) + 1;
        descompositionOfA.resize(sqrtOfN);
        sumOfDescomposition.resize(sqrtOfN, 0);

        forn(i, n) descompositionOfA[i/sqrtOfN].pb(A[i]);
        
        forn(i, sqrtOfN){
            forn(j, SIZE(descompositionOfA[i])) sumOfDescomposition[i] += descompositionOfA[i][j];
        }
    }
    
    int findBlock(int index){
		return index/sqrtOfN;
	}
	
	int findIndexInTheBlock(int index){
		return index % sqrtOfN;
	}
    
    void answerQuery(int l, int r){
		int blockOfL = findBlock(l), blockOfR = findBlock(r);
		int indexOfL = findIndexInTheBlock(l), indexOfR = findIndexInTheBlock(r);
		ll res = 0;
		
		if (blockOfL == blockOfR){
			forsn(i, indexOfL, indexOfR+1) res += descompositionOfA[blockOfL][i];
		} else {
			forsn(i, indexOfL, SIZE(descompositionOfA[blockOfL])) res += descompositionOfA[blockOfL][i];
			forn(i, indexOfR+1) res += descompositionOfA[blockOfR][i];
			forsn(i, blockOfL+1, blockOfR) res += sumOfDescomposition[i];
		}
		
		cout << res << "\n";
	}
	
	void updateAt(int l, ll v){
		int blockOfL = findBlock(l), indexOfL = findIndexInTheBlock(l);
		sumOfDescomposition[blockOfL] -= descompositionOfA[blockOfL][indexOfL];
		descompositionOfA[blockOfL][indexOfL] = v;
		sumOfDescomposition[blockOfL] += descompositionOfA[blockOfL][indexOfL];
	}
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, q;
	cin >> n >> q;
	
	vl A(n);
	forn(i, n) cin >> A[i];
	SqrtDescomposition S(A);
	
	forn(_, q){
		int k, l, r;
		cin >> k >> l >> r;
		l--;
		
		if (k == 1) S.updateAt(l, r);
		else {
			r--; 
			S.answerQuery(l, r);
		}
	}
	
    return 0;
}
