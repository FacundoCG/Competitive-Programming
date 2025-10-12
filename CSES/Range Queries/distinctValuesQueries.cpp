#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vl = vector<ll>;
using ii = pair<int,int>;

template <typename T>
using vv = vector<vector<T>>;

const ll UNDEFINED = -1;
const int MAX_N = 2*1e5 + 1;
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

int A[MAX_N], B[MAX_N];
int n;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void remove(int x, int &res){
	B[x]--;
	res -= (B[x] == 0);
}

void add(int x, int &res){
	B[x]++;
	res += (B[x] == 1);
}

int block_size;

struct Query {
    int l, r, idx;
    
    Query(int L, int R, int ID) : l(L), r(R), idx(ID){}
    
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

vi mo_s_algorithm(vector<Query> &queries) {
    block_size = (int) sqrt(n)+1;
    vi answers(SIZE(queries));
    sort(all(queries));

	int res = 0;
    int cur_l = 0, cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(A[cur_l], res);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(A[cur_r], res);
        }
        while (cur_l < q.l) {
            remove(A[cur_l], res);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(A[cur_r], res);
            cur_r--;
        }
        answers[q.idx] = res;
    }
    return answers;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	
	int q;
	cin >> n >> q;
	
	forn(i, n) B[i] = 0; 
	forn(i, n) cin >> A[i];
	vector<Query> queries;
	unordered_map<int, int, custom_hash> m;
	
	int k = 0;
	forn(i, n){
		if (!esta(A[i], m)) m[A[i]] = k++;
		A[i] = m[A[i]];
	}
	
	forn(i, q){
		int a, b;
		cin >> a >> b;
		a--; b--;
		queries.pb(Query(a, b, i));
	}
	
	vi answers = mo_s_algorithm(queries);
	forn(i, q) cout << answers[i] << "\n";
	
    return 0;
}
