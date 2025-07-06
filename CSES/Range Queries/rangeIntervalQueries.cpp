#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 1e6 + 1;
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
    vi A;
    vector<vi> descompositionOfA;
    vector<vi> sortDescompositions;
    int n, sqrtOfN;

    SqrtDescomposition(vi &arr) : A(arr){
        n = SIZE(arr);
        sqrtOfN = (int) sqrt(n) + 1;
        descompositionOfA.resize(sqrtOfN);
        sortDescompositions.resize(sqrtOfN);

        forn(i, n) {
			descompositionOfA[i/sqrtOfN].pb(A[i]);
			sortDescompositions[i/sqrtOfN].pb(A[i]);
		}
		
		forn(i, sqrtOfN) sort(all(sortDescompositions[i]));
    }

    int findBlock(int index){
		return index/sqrtOfN;
	}
	
	int findIndexInTheBlock(int index){
		return index % sqrtOfN;
	}
	
	// Calcular extremo derecho que cumple P(X)
	int rightBinarySearch(int start, int end, vi &B, int v){
		int l = start - 1;
		int r = end + 1;

		while (r - l > 1){
			int mid = (l + r)/2;

			if (B[mid] <= v){
				l = mid;
			} else {
				r = mid;
			}
		}
		
		if (l < start || l > end || !(B[l] <= v)) l = -1; // Si l no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
		
		return l; // l es el ultimo elemento que cumple P(X)
	}

	// Calcular extremo izquierdo que cumple P(X)
	int leftBinarySearch(int start, int end, vi &B, int v){
		int l = start - 1; 
		int r = end + 1; 

		while(r - l > 1) { 
			int mid = (l + r) / 2;
			if(!(B[mid] >= v)) {
				l = mid;
			} else {
				r = mid;
			}
		}
		
		if (r < start || r > end || !(B[r] >= v)) r = -1; // Si r no está en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1

		return r; // r es el primer elemento que cumple P(X)
	}
	
    
    int answerQuery(int l, int r, int c, int d){
		int blockOfL = findBlock(l), blockOfR = findBlock(r);
		int indexOfL = findIndexInTheBlock(l), indexOfR = findIndexInTheBlock(r);
		int res = 0;
		
		if (blockOfL == blockOfR){
			forsn(i, indexOfL, indexOfR+1) res += (c <= descompositionOfA[blockOfL][i] && descompositionOfA[blockOfL][i] <= d);
		} else {
			forsn(i, indexOfL, SIZE(descompositionOfA[blockOfL])) res += (c <= descompositionOfA[blockOfL][i] && descompositionOfA[blockOfL][i] <= d);
			forn(i, indexOfR+1) res += (c <= descompositionOfA[blockOfR][i] && descompositionOfA[blockOfR][i] <= d);
			forsn(i, blockOfL+1, blockOfR){
				int left = leftBinarySearch(0, SIZE(sortDescompositions[i])-1, sortDescompositions[i], c);
				int right = rightBinarySearch(0, SIZE(sortDescompositions[i])-1, sortDescompositions[i], d);
				if (left != UNDEFINED && right != UNDEFINED) res += right - left + 1;
			}
		}
		
		return res;
	}
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, q;
	cin >> n >> q;
	
	vi A(n);
	forn(i, n) cin >> A[i];
	SqrtDescomposition S(A);
	
	forn(_, q){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--; b--;
		cout << S.answerQuery(a, b, c, d) << "\n";
	}
	
    return 0;
}
