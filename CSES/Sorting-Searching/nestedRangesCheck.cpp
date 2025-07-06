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

typedef pair<int, int> interval;

// Esta función chequea si p1 está incluido en p2
bool isIncluded(interval &p1, interval &p2){
    ll startingTimeP1 = p1.first, endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first, endingTimeP2 = p2.second;
    return startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;;
}

// Si p1 < p2, puede pasar que:
// Si p1.snd = p2.snd, entonces p2 está contenido en p1 ya que p1.fst < p2.fst
// Si p1.snd < p2.snd, entonces p1 no puede contener a p2 ni a ningún intervalo a la derecha de p2 ya que también van a ser > p1.snd 

bool finishEarlier(pair<interval, int> &a1, pair<interval, int> &a2){
	interval p1 = a1.fst, p2 = a2.fst;
    ll endingTimeP1 = p1.second, endingTimeP2 = p2.second;
    if (endingTimeP1 != endingTimeP2) return endingTimeP1 < endingTimeP2;
    ll startingTimeP1 = p1.first, startingTimeP2 = p2.first;
    return startingTimeP1 < startingTimeP2;
}

// Sea p1 < p2, puede pasar que: 
// Si p1.fst = p2.fst, entonces p2 está incluido en p1 ya que p1.snd > p2.snd
// Si p1.fst < p2.fst, entonces p2 puede estar incluido en p1, o puede estar a la derecha, es decir, [p1.fst, ..., p2.fst, ..., p1.snd, ..., p2.snd]

bool startEarlier(pair<interval, int> &a1, pair<interval, int> &a2){
	interval p1 = a1.fst, p2 = a2.fst;
    ll startingTimeP1 = p1.first, startingTimeP2 = p2.first;
    if (startingTimeP1 != startingTimeP2) return startingTimeP1 < startingTimeP2;
    ll endingTimeP1 = p1.second, endingTimeP2 = p2.second;
    return endingTimeP1 > endingTimeP2;
}


int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	vector<pair<interval, int>> A(n);
	forn(i, n){
		int l, r;
		cin >> l >> r;
		A[i] = {{l, r}, i};
	}
	
	sort(all(A), startEarlier);	// A[i+1] está incluido en A[i] o A[i+1] está a la derecha de A[i] y los intervalos siguientes también
	vector<int> isContained(n), contains(n);
	
	// Mal terminar antes: [2, 4], [1, 6]  
	// Mal empezar antes: [1, 4], [2, 6], [3, 4]
	
	interval lastInterval = A[0].fst;
	set<pair<int, int>> s;
	s.insert({lastInterval.snd, A[0].snd});
	
	forsn(i, 1, n){
		int endingTime = A[i].fst.snd;
		auto it = s.lower_bound({endingTime, -1});
		for (auto k = it; k != s.end(); k++) contains[(*k).snd] = 1;
		s.erase(it, s.end());
		s.insert({endingTime, A[i].snd});
	}
		
	lastInterval = A[0].fst;
	
	forsn(i, 1, n){
		interval currentInterval = A[i].fst;
		if (isIncluded(currentInterval, lastInterval)){
			 isContained[A[i].snd] = 1;
		} else {
			lastInterval = currentInterval;
		}
	}
	
	forn(i, n) cout << contains[i] << " ";
	cout << "\n";
	forn(i, n) cout << isContained[i] << " ";
	cout << "\n";
    return 0;
}
