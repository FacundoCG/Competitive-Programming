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

// ############################################################### //

struct LexicographicalComparator {
    bool operator()(const pair<ll, ll> & a, const pair<ll, ll> & b) const {
        return a > b; // Use operator > for min-heap
    }
};

vector<ll> djikstra (ll v, vector<vector<pair<ll, ll>>> &adjList){ // Time complexity: O(|E| * log(|V|))
    int n = adjList.size();
    vector<ll> distances(n, LINF);
    vector<ll> visited(n, false);
    priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, LexicographicalComparator> q;
    distances[v] = 0;
    q.push({0, v});
 
    while (!q.empty()){
        ll u = q.top().second;
        q.pop();
 
        if (visited[u]){
            continue;
        }
 
        visited[u] = true;
 
        for (ll i = 0; i < adjList[u].size(); i++){
            ll weightEdge = (ll) adjList[u][i].first;
            ll w = (ll) adjList[u][i].second;
            ll oldDistance = (ll) distances[w];
            ll newDistance = (ll) weightEdge + distances[u];
 
            if (oldDistance > newDistance){
                distances[w] = (ll) newDistance;
                q.push({distances[w], w});
            }
        }
    }
 
    return distances;
}

void solve(vector<ll> &A, vector<ll> &B){
    vector<ll> prefixSum(SIZE(A));
    
    prefixSum[1] = A[1];
    forsn(i, 2, SIZE(A)) prefixSum[i] = prefixSum[i-1] + A[i];
    
    // I will calculate what is the minimum loss if I want my path to go from index 1 to j. The score will be: prefixSum[j] - loss
    // I want this loss to be minimum and it can't repeat indexs in the path. I will model a directed weighted graph and look for the minimum path
    
    vector<vector<pair<ll, ll>>> adjList(SIZE(A));
    
    // I need to add edges when I skip and when I submit a problem
    // When I submit the i-th problem, I have a loss of 0 and goes to the vertex i-1
    forsn(i, 2, SIZE(A)) adjList[i].pb({0, i-1}); 
    
    // When I skip the i-th problem, I have a loss of A[i] and goes to the vertex B[i]
    forsn(i, 1, SIZE(A)) adjList[i].pb({A[i], B[i]});
    
    // Now, I calculate the minimum path from 1 to the other vertexs with Djikstra
    ll res = 0;
    vector<ll> minimumLossFrom1 = djikstra(1, adjList);
            
    forsn(i, 1, SIZE(A)){
        res = max(res, prefixSum[i] - minimumLossFrom1[i]);
    }
    
    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
	
	forn(_, t){
		ll n;
		cin >> n;
		
		vector<ll> A(n+1);
		vector<ll> B(n+1);
		
		forsn(i, 1, n+1) cin >> A[i];
		forsn(i, 1, n+1) cin >> B[i];
		solve(A, B);
	}
}
