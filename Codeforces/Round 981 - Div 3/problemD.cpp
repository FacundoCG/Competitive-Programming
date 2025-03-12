#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

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
#define forall(i,c) for(auto i=(c).begin(), i != (c).end(); i++)
#define dforall(i,c) for(auto i=(c).rbegin(), i != (c).rend(); i--)

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

// Show pair
template <typename T1, typename T2>
ostream & operator <<(ostream &os, const pair<T1, T2> &p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

int leftBinarySearch(int start, int end, ll value, vector<ll> &A){
    int l = start - 1; 
    int r = end + 1; 
	
	//DBG(l);
	//DBG(r);
	
    while(r - l > 1) { 
        int mid = (l + r) / 2;
        //DBG(mid);
        if(!(A[mid] >= value)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    if (r > end || A[r] < value) r = -1;

    return r; // r es el primer elemento que cumple P(X) o -1 si no existe dicho elemento
}

void solve(vector<int> &numbers){
    vector<ll> prefixSum(SIZE(numbers));
    prefixSum[0] = numbers[0];
    forsn(i, 1, SIZE(numbers)) prefixSum[i] = (ll) prefixSum[i-1] + numbers[i];
    //DBG(prefixSum);
    map<ll, vector<ll>> positionsElements;
    forn(i, SIZE(numbers)) positionsElements[prefixSum[i]].pb(i);
    
    for(auto i : positionsElements){
		//DBG(i);
		//RAYA;
	}
    
    int i = 0;
    ll lastPositionOfInterval = UNDEFINED;
    int res = 0;
	
	while (i < SIZE(numbers)){
		// I need to find the first apparition of currentZero with an index >= i. Let's be that j
		// The interval determined is: [i, j]
		// If j < lastPositionInterval: lastPositionInterval = j
		// If j > lastPositionInterval: I don't do anything
		// If i > lastPositionInterval: res++ and lastPositionInterval = j
		//DBG(i);
		ll currentZero = 0;
		if (i > 0) currentZero = prefixSum[i-1];
		ll newLastInterval = UNDEFINED; // Originally, I put it UNDEFINED because I don't know if there is an index which makes zero from this index
		//DBG(currentZero);
		
		if (esta(currentZero, positionsElements)){
			int n = SIZE(positionsElements[currentZero]) - 1;
			newLastInterval = leftBinarySearch(0, n, i, positionsElements[currentZero]);
			if (newLastInterval != UNDEFINED) newLastInterval = positionsElements[currentZero][newLastInterval];
		}
		
		//DBG(lastPositionOfInterval);
		//DBG(newLastInterval);
		
		if (i > lastPositionOfInterval && newLastInterval != UNDEFINED){ // If I have a new nonoverlapping interval, I add it
			lastPositionOfInterval = newLastInterval;
			res++;
		} else if (newLastInterval < lastPositionOfInterval && newLastInterval != UNDEFINED) { // If I have a new overlapping interval, I will use it as the new last interval if it is shorter than the previous one
			lastPositionOfInterval = newLastInterval;
		}
		//RAYA;
		i++;
	}
	
    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
		int n;
        cin >> n;

        vector<int> numbers(n);
        forn(i, n) cin >> numbers[i];
        solve(numbers);
        // -1 4 0 -3 4 
    }
}
