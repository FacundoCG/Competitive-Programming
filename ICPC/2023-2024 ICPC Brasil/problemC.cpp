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

vector<bool> visited;

int binary_search(vector<int>& A, int i, int j, int k){
    if (i >= j){
        return j;
    }

    int middle = (i/2) + (j/2);

    if (A[middle] == k){
        return middle;
    } else if (k < A[middle]){
        return binary_search(A, i, middle, k);
    } else {
        return binary_search(A, middle + 1, j, k);
    }
}

void dfs(int v, vector<int> &res, vector<vector<int>> &adjList, vector<int> &lis, vector<int> &val){
	visited[v] = true;
	res[v] = SIZE(lis);
	
	for (int w : adjList[v]){
		if (!visited[w]){
			if (val[w] > lis.back()){
				lis.pb(val[w]);
				dfs(w, res, adjList, lis, val);
				lis.pop_back();
			} else {
				int positionElementIth = binary_search(lis, 0, SIZE(lis)-1, val[w]);
				int oldValue = lis[positionElementIth];
				lis[positionElementIth] = val[w];
				dfs(w, res, adjList, lis, val);
				lis[positionElementIth] = oldValue;
			}
		}
	}
}
 
 
int main()
{
	cin.tie(0);
    cin.sync_with_stdio(0);
    
	int n;
	cin >> n;
	
	vector<vector<int>> adjList(n+1);
	vector<int> val(n+1);
	vector<int> res(n+1);
	visited.resize(n+1);
	
	forsn(i, 2, n+1){
		int p;
		cin >> p;
		adjList[i].pb(p);
		adjList[p].pb(i);
	}
	
	forsn(i, 1, n+1) cin >> val[i];
	vector<int> lis;
	lis.pb(val[1]);
	
	dfs(1, res, adjList, lis, val);
	
	forsn(i, 2, n+1){
		cout << res[i] << " ";
	}
	
	cout << "\n";
    return 0;
}
