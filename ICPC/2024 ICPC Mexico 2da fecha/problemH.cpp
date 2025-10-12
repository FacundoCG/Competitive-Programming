#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;

using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll UNDEFINED = -1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;



#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define SIZE(c) int((c).size())


#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "------------------" << endl

#define forn(i, n) for (int i=0;i<(int)(n); i++)
#define forsn(i, s, n) for (int i=(s);i<(int)(n); i++)

// Show vector

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v){
    os << "[";
    forn(i, v.size()){
        if(i>0) os << ",";
        os << v[i];
    }
    return os << "]";
}

int leftPeople;

int personToDeleteFrom(vi &succ, int pos, int x){
	x %= leftPeople;
	//~ DBG(x);
	int res = pos;
	forn(_, x) { res = succ[res];} // 1 = succ[1] = 2 - > succ[2] = 3
	return res;
}

void updateAfterEliminated(int x, vi &succ, vi &prev){
	succ[prev[x]] = succ[x];
	prev[succ[x]] = prev[x];
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int n, r, c;
	cin >> n >> r >> c;
	r--; c--;
	
	vi eliminated(n+1, false), isGood(n+1, false);
	vi succ(n+1), prev(n+1);
	
	forsn(i, 1, n) succ[i] = i+1;
	succ[n] = 1;
	
	forsn(i, 2, n+1) prev[i] = i-1;
	prev[1] = n;
	
	//~ DBG(succ); DBG(prev);
	
	leftPeople = n;
	int pos1 = 1, pos2 = n;
	//~ DBG(pos1); DBG(pos2);
	
	while (leftPeople > 2){
		int toDelete1 = personToDeleteFrom(succ, pos1, r);
		int toDelete2 = personToDeleteFrom(prev, pos2, c);
		//~ DBG(toDelete1); DBG(toDelete2);
		
		eliminated[toDelete1] = true;
		eliminated[toDelete2] = true;
		
		if (toDelete1 == toDelete2){
			isGood[toDelete1] = true;
			pos1 = succ[toDelete1];
			pos2 = prev[toDelete1];
			updateAfterEliminated(toDelete1, succ, prev);
			leftPeople--;
		} else {
			pos1 = succ[toDelete1];
			updateAfterEliminated(toDelete1, succ, prev);
			if (toDelete2 == pos1) pos1 = succ[toDelete2];
			pos2 = prev[toDelete2];
			updateAfterEliminated(toDelete2, succ, prev);
			leftPeople -= 2;
		}
	}
	
	vi candidates;
	
	forsn(i, 1, n+1){
		if (!eliminated[i]) isGood[i] = true; 
	}
		
	forsn(i, 1, n+1){
		if (isGood[i]) candidates.pb(i);
	}
	
	for (int id : candidates) cout << id << " ";
	cout << "\n";
	
    return 0;
}
