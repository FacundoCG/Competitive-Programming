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

bool customCompare(pair<ll,ll> p1, pair<ll,ll> p2){
	return p1.first + p1.second < p2.first + p2.second; // I will have first those boxes whose sum is smaller
}

void solve(vector<pair<ll,ll>> &boxes){
	vector<ll> bestWeightSupportedForEachBox(SIZE(boxes)); // This array tells me if the ith-box can support a maximum of k boxes, which is the sum supported there
	vector<ll> res(SIZE(boxes), 1); // Each box support at least one box (itself)
	
	forn(i, SIZE(boxes)){
		bestWeightSupportedForEachBox[i] = boxes[i].first; // Initially each box support its own weight
	}
	
	forn(i, SIZE(boxes)){ // i is the box that I want to add to the stack
		forsn(j, i+1, SIZE(boxes)){ // j is the box that I want to check if support i and its options
			if (bestWeightSupportedForEachBox[i] <= boxes[j].second){ // It means that I can add the box i with its best boxes to the stack
				if (res[j] < res[i] + 1){ // If adding this box I obtain a better res
					res[j] = res[i] + 1; // I update this res
					bestWeightSupportedForEachBox[j] = bestWeightSupportedForEachBox[i] + boxes[j].first; // I update its weight
				} else if (res[j] == res[i] + 1){
					bestWeightSupportedForEachBox[j] = min(bestWeightSupportedForEachBox[i] + boxes[j].first, bestWeightSupportedForEachBox[j]);
				}
			}
		}
	}
	
	ll a = 0;
	
	forn(i, SIZE(res)){
		a = max(res[i], a);
	}
	
	//DBG(boxes);
	//DBG(res);
	
	cout << a << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int x
}
