#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vb = vector<bool>;

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

using position = pair<int, int>;

struct Graph{
	position start, end;
	vector<string> A;
	int n, m;
	vector<vb> visited;
	vector<vi> distances, buildPath;
	
	Graph(vector<string> &map, int height, int width) : A(map), n(height), m(width){
		forn(i, n){
			forn(j, m){
				if (A[i][j] == 'A'){
					start = {i, j};
				}
				
				if (A[i][j] == 'B'){
					end = {i, j};
				}
			}
		}
		
		visited.resize(n, vector<bool>(m, false));
		distances.resize(n, vector<int>(m, INF));
		buildPath.resize(n, vector<int>(m, UNDEFINED));
	}
	
	bool validPosition(int x1, int y1){
		if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m) return false;
		if (A[x1][y1] == '#' || visited[x1][y1]) return false;
		return true;
	}
	
	void visitNeighbor(int x0, int y0, int x1, int y1, queue<position> &q){
		if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m) return ;
		if (A[x1][y1] == '#' || visited[x1][y1]) return ;
		
		distances[x1][y1] = distances[x0][y0] + 1;
		visited[x1][y1] = true;
		q.push({x1, y1});
	}
	
	void solve(){
		queue<position> q;
		q.push(start);
		visited[start.fst][start.snd] = true;
		distances[start.fst][start.snd] = 0;
		
		while (!q.empty()){
			position currentPosition = q.front();
			q.pop();
			
			int x = currentPosition.fst, y = currentPosition.snd;
			
			if (validPosition(x+1, y)){
				distances[x+1][y] = distances[x][y] + 1;
				visited[x+1][y] = true;
				q.push({x+1, y});
				buildPath[x+1][y] = 1; // I have to  do x -= 1;
			}
			
			if (validPosition(x-1, y)){
				distances[x-1][y] = distances[x][y] + 1;
				visited[x-1][y] = true;
				q.push({x-1, y});
				buildPath[x-1][y] = 2; // I have to  do x += 1;
			}
			
			if (validPosition(x, y+1)){
				distances[x][y+1] = distances[x][y] + 1;
				visited[x][y+1] = true;
				q.push({x, y+1});
				buildPath[x][y+1] = 3; // I have to  do y -= 1;
			}
			
			if (validPosition(x, y-1)){
				distances[x][y-1] = distances[x][y] + 1;
				visited[x][y-1] = true;
				q.push({x, y-1});
				buildPath[x][y-1] = 4; // I have to  do y += 1;
			}
			
				
		}
		
		if (!visited[end.fst][end.snd]){
			cout << "NO\n";
			return ;
		}
		
		cout << "YES\n";
		cout << distances[end.fst][end.snd] << "\n";
	
		int currentX = end.fst, currentY = end.snd;
		vector<char> path;
		while (buildPath[currentX][currentY] != UNDEFINED){
			if (buildPath[currentX][currentY] == 1){
				currentX--; path.pb('D');
			} else if (buildPath[currentX][currentY] == 2){
				currentX++; path.pb('U');
			} else if (buildPath[currentX][currentY] == 3){
				currentY--; path.pb('R');
			} else {
				currentY++; path.pb('L');
			}
		}
		
		dforn(i, SIZE(path)) cout << path[i];
		cout << "\n";
	}
};

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<string> A(n);
	forn(i, n) cin >> A[i];
	
	Graph G(A, n, m);
	G.solve();
	
    return 0;
}
