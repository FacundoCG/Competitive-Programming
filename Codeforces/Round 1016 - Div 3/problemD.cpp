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

void findCellOf(ll v, ll width, ll start, ll end, ll rowStart, ll colStart){
	if (width == 2){
		ll resRow = rowStart;
		ll resCol = colStart;
		
		if (v == start + 1){
			resRow++; resCol++;
		} else if (v == start + 2){
			resRow++;
		} else {
			resCol++;
		}
		
		cout << resRow << " " << resCol << "\n";
	} else {
		ll newSize = width/2;		
		ll end1 = end/4;
		ll end2 = end1*2;
		ll end3 = 3*end1;
		ll end4 = 4*end1;
		
		ll start2 = (ll) end1 + 1;
		ll start3 = (ll) end2 + 1;
		ll start4 = (ll) end3 + 1;
		
		ll row2 = (ll) rowStart + newSize;
		ll col2 = (ll) colStart + newSize;
		
		if (start <= v && v <= end1) findCellOf(v, newSize, start, end1, rowStart, colStart);
		if (start2 <= v && v <= end2) findCellOf(v, newSize, start2, end2, row2, col2);
		if (start3 <= v && v <= end3) findCellOf(v, newSize, start3, end3, row2, colStart);
		if (start4 <= v && v <= end4) findCellOf(v, newSize, start4, end4, rowStart, col2);
	}
}

void findNumberInCell(ll x, ll y, ll width, ll start, ll end, ll rowStart, ll colStart){
	if (width == 2){
		ll res;
		if (x == rowStart && colStart == y) res = start;
		else if (x == rowStart+1 && y == colStart + 1) res = (ll) start + 1;
		else if (x == rowStart+1 && y == colStart) res = (ll) start + 2;
		else if (x == rowStart && y == colStart + 1) res = (ll) start + 3;
		cout << res << "\n";
	
	} else {
		ll newSize = width/2;		
		ll end1 = end/4;
		ll end2 = end1*2;
		ll end3 = 3*end1;
		ll end4 = 4*end1;
		
		ll start2 = (ll) end1 + 1;
		ll start3 = (ll) end2 + 1;
		ll start4 = (ll) end3 + 1;
		
		ll row2 = (ll) rowStart + newSize;
		ll col2 = (ll) colStart + newSize;
		
		ll limitRow = (ll) rowStart + width;
		ll limitCol = (ll) colStart + width;
		
		if (rowStart <= x && x < row2 && colStart <= y && y < col2) findNumberInCell(x, y, newSize, start, end1, rowStart, colStart);
		if (row2 <= x && x < limitRow && col2 <= y && y < limitCol) findNumberInCell(x, y, newSize, start2, end2, row2, col2);
		if (row2 <= x && x < limitRow && colStart <= y && y < col2) findNumberInCell(x, y, newSize, start3, end3, row2, colStart);
		if (rowStart <= x && x < row2 && col2 <= y && y < limitCol) findNumberInCell(x, y, newSize, start4, end4, rowStart, col2);
	}
}

int main() {
    //~ ios :: sync_with_stdio(0);
    //~ cin.tie(0);
	
	int t;
	cin >> t;
	
	forn(_, t){
		ll n, q;
		cin >> n >> q;
		cin.ignore();
		
		ll width = (ll) pow(2, n);
		ll endInterval = (ll) pow(2, 2*n);
				
		forn(i, q){
			string line;
			getline(cin, line);
			
			stringstream ss(line);
			string direction;
			ss >> direction;
			
			if (direction == "->"){
				ll x, y;
				ss >> x >> y;
				findNumberInCell(x, y, width, 1, endInterval, 1, 1);
			} else {
				ll d;
				ss >> d;
				findCellOf(d, width, 1, endInterval, 1, 1);
			}
		}
	}
}
