#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> edge;

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

int minDistances[100][100];
int neighbors[100];
bool edgesUsed[100][100];
int n;

bool floydWarshall(){
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (minDistances[i][k] != INF && minDistances[k][j] != INF){
                    int newDistance = (int) minDistances[i][k] + minDistances[k][j];
                    if (newDistance < minDistances[i][j]){
						return false;
					}
                    minDistances[i][j] = min(minDistances[i][j], newDistance);
                }
            }
        }
    }
    
    return true;
}

struct LexicographicalComparator {
    bool operator()(const pair<int, int> & a, const pair<int, int> & b) const {
        return a > b; // Use operator > for min-heap
    }
};

bool djikstra (int v, vector<set<pair<int, int>>> &adjList){ // Time complexity: O(|E| * log(|V|))
    vector<int> distances(n, INF);
    vector<int> timesUsed(n, 0);
    vector<int> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int,int>>, LexicographicalComparator> q;
    distances[v] = 0;
    q.push({0, v});
 
    while (!q.empty()){
        int u = q.top().second;
        q.pop();
 
        if (visited[u]){
            continue;
        }
 
        visited[u] = true;
 
        for (auto e : adjList[u]){
			int w = (int) e.second;
            int weightEdge = (int) e.first;
            int oldDistance = (int) distances[w];
            int newDistance = (int) weightEdge + distances[u];
			timesUsed[w]++;
            if (edgesUsed[u][w] && oldDistance > newDistance){
                distances[w] = (int) newDistance;
                q.push({distances[w], w});
            }
            
            if (timesUsed[w] == neighbors[w] && distances[w] > minDistances[v][w]){
				return false;
			}
        }
    }
 
    return true;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    
    vector<set<edge>> adjList(n);
    vector<pair<int, int>> edges;
    
    forn(i, 100){
		forn(j, 100) edgesUsed[i][j] = false;
	}
	
	forn(i, 100) neighbors[i] = n-1;
    
    forn(i, n){
		forn(j, n) {
			cin >> minDistances[i][j];
			if (i != j){
				int weight = minDistances[i][j];
				adjList[i].insert({weight, j});
				if (!edgesUsed[i][j] && !edgesUsed[j][i]){
					edges.pb({i, j});
				}
				edgesUsed[i][j] = true;
			}
		}
	}
	
	bool flag = floydWarshall();
	
	if (!flag){
		cout << -1 << "\n";
		return 0;
	}
	
	int res = 0;

	for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (minDistances[i][k] != INF && minDistances[k][j] != INF){
                    int newDistance = (int) minDistances[i][k] + minDistances[k][j];
                    if (edgesUsed[i][j] && edgesUsed[j][i] && k != i && k != j && newDistance == minDistances[i][j]){
						res++;
						minDistances[i][j] = INF;
						edgesUsed[i][j] = false;
						edgesUsed[j][i] = false;
					}
                }
            }
        }
    }
	
	cout << res << "\n";
}
