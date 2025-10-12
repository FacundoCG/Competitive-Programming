#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;
using vvi = vector<vi>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;

#define pb push_back
#define fst first
#define snd second

#define esta(x, c) ((c).find(x) != (c).end())
#define all(c) (c).begin(),(c).end()
#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << "=" << (x) << endl;
#define RAYA cerr << "-----------" << endl;

#define forn(i, n) for(int i=0; i<(int)(n);i++)
#define forsn(i, s, n) for(int i=(s); i<(int)(n);i++)

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
	os << "[";
	forn(i, SIZE(v)){
		if (i > 0) os << ",";
		os << v[i];
	}
	return os << "]";
}

// ######################## //

unordered_map<int, int> M;
vector<vi> adjList;

void dfs(int v, unordered_set<int> &s, vi &res, vi &groups){
	s.insert(groups[v]);
	M[groups[v]]++;
	res[v] = SIZE(s);
	
	for (int u : adjList[v]) dfs(u, s, res, groups);
	
	M[groups[v]]--;
	if (M[groups[v]] == 0) s.erase(groups[v]);
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n;
	cin >> n;
	
	int supervisor = 0;
	
	adjList.resize(n+1);
	forsn(i, 1, n+1){
		int boss;
		cin >> boss;
		if (boss == 0) supervisor = i;
		adjList[boss].pb(i);
	}
	
	unordered_set<int> s;
	vi res(n+1, 0), groups(n+1, UNDEFINED);
	forsn(i, 1, n+1) cin >> groups[i];
	dfs(supervisor, s, res, groups);
	forsn(i, 1, n+1) cout << res[i] << " ";
	cout << "\n";
	
	return 0;
}
