#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using vi = vector<int>;

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

// ######################## //

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	int soldiers = n/k;
	if (soldiers >= m) cout << "Iron fist Ketil\n";
	else cout << "King Canute\n";
	
	return 0;
}
