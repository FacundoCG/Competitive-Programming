#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

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

int a, b;

struct MaximumSubarrayFromMiddle{
	vl leftPrefixSum, rightPrefixSum, rightMaxPrefix;
	ll bestSumMiddle;
	
	MaximumSubarrayFromMiddle(vl &A){
		int n = SIZE(A), middle = n/2;
		leftPrefixSum = {0}; rightPrefixSum = {0};
		dforn(i, middle) leftPrefixSum.pb(A[i] + leftPrefixSum[SIZE(leftPrefixSum)-1]);
		forsn(i, middle+1, n) rightPrefixSum.pb(A[i] + rightPrefixSum[SIZE(rightPrefixSum)-1]);
		rightMaxPrefix.resize(SIZE(rightPrefixSum), 0);
		forsn(i, 1, SIZE(rightPrefixSum)) rightMaxPrefix[i] = max(rightMaxPrefix[i-1], rightPrefixSum[i]);

		bestSumMiddle = A[middle];
	}
	
	ll calculate(){
		ll res = (-1) * LINF;
		
		// Tengo que elegir un intervalo  >= a-1 y <= b-1
		
		forsn(i, a-1, min(b, SIZE(leftPrefixSum))){ // Elijo un intervalo izquierdo entre [a-1, b-1]
			ll currentRes = leftPrefixSum[i];
			int sizeAvailable = b-1-i;
			if (sizeAvailable < SIZE(rightMaxPrefix)) currentRes += rightMaxPrefix[sizeAvailable];
			res = max(res, currentRes);
		}
		
		int windowSize = b - 1 - (a - 1);
		// Ahora tengo que elegir intervalos entre [0, a-2]
		// Si elijo 0, busco max de rightPrefixSum entre [a-1, a-1+windowSize]
		// Si elijo 1, busco max de rightPrefixSum entre [a-2, a-2+windowSize]
		// ...
		// Si elijo a-2, busco más entre [1, 1+windowSize]
		dforn(i, min(SIZE(leftPrefixSum), a-1)){
			
		}
		
		res += bestSumMiddle;
		return bestSumMiddle;
	}
};

ll maximumSubArraySum(vl &A){
    ll res = 0;
    int n = SIZE(A);
	
	if (n < a) return (-1)*LINF;
    if (n == 1) return A[0];
    else if (n == 0) return (-1)*LINF; // Esto es para no permitir array vacío

    int middle = n/2;
    vl left, right;

    forn(i, middle) left.pb(A[i]);
    forsn(i, middle, n) right.pb(A[i]);
    
    MaximumSubarrayFromMiddle M(A);
    ll middleSum = M.calculate(), leftSum = maximumSubArraySum(left), rightSum = maximumSubArraySum(right);
    res = max(middleSum, max(leftSum, rightSum));
    return res;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n >> a >> b;
	
	vl A(n);
	forn(i, n) cin >> A[i];
	
	ll res = maximumSubArraySum(A);
	cout << res << "\n";
	
	
    return 0;
}
