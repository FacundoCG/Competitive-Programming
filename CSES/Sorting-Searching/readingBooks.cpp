#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

const ll UNDEFINED = -1;
const int MAX_N = 2*1e5;
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

int n;
vector<ll> A;

ll solve(int i, ll leftSum, ll rightSum){
	//~ DBG(i); DBG(leftSum); DBG(rightSum); DBG(A);
	
	ll totalTimeToReadRightBooks, totalTimeToReadLeftBooks;
	vector<ll> suffixSum(n+1), prefixSum(n+1);	
	dforn(j, n) suffixSum[j] = suffixSum[j+1] + A[j];
	forsn(j, 1, n+1) prefixSum[j] = prefixSum[j-1] + A[j-1];
	//~ DBG(suffixSum); DBG(prefixSum);
	
	if (leftSum <= rightSum){
		// rightSum es lo que me tomo leer A[i+1], ..., A[n-1]
		// leftSum es lo que me tomo leer A[0], ..., A[i-1]
		//~ cout << "Acá\n";
		totalTimeToReadRightBooks = leftSum + suffixSum[i] + max(rightSum - (prefixSum[n] - A[i+1]), 0ll);
		totalTimeToReadLeftBooks = rightSum + prefixSum[i+1] + max(leftSum + A[i] - (prefixSum[n] - A[i]), 0ll);
	} else {
		totalTimeToReadLeftBooks = rightSum + prefixSum[i+1] + max(leftSum - (prefixSum[n] - A[i-1]), 0ll);
		totalTimeToReadRightBooks = leftSum + suffixSum[i] + max(rightSum + A[i] - (prefixSum[n] - A[i]), 0ll);
	}
	
	return max(totalTimeToReadRightBooks, totalTimeToReadLeftBooks);
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	cin >> n;
	A.resize(n);
	forn(i, n) cin >> A[i];
	sort(all(A));
	
	if (n == 1){
		cout << A[0]*2 << "\n";
		return 0;
	} else if (n == 2){
		ll totalSum = A[0] + A[1];
		cout << totalSum + A[1] - A[0] << "\n";
		return 0;
	}
	
	int i = 0;
	int j = n-1;
	ll res = 0;
	ll leftSum = 0;
	ll rightSum = 0;
	
	while (i <= j){
		if (i == j){			
			res = solve(i, leftSum, rightSum);
			i++;
		} else {
			if (leftSum <= rightSum){ leftSum += A[i]; i++;} 
			else { rightSum += A[j]; j--;}
		}
	}
	
	cout << res << "\n";
	
    return 0;
}
