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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_multiset = tree<
    pair<T, int>,
    null_type,
    less<pair<T, int>>, // NOT less_equal
    rb_tree_tag,
    tree_order_statistics_node_update
>;

int indexOfMedian;
ll leftLen, rightLen, leftSum, rightSum;

ll get_answer(ordered_multiset<ll> &s){
	ll median = (*s.find_by_order(indexOfMedian)).fst;
	ll res = (leftLen*median - leftSum) + (rightSum - rightLen*median);
	return res;
}

void update(int indexOf, ll v, int s){
	if (indexOf < indexOfMedian) leftSum += v*s;
	else if (indexOf > indexOfMedian) rightSum += v*s;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, k;
    cin >> n >> k;
    
    vector<ll> A(n);
    forn(i, n) cin >> A[i];
    ordered_multiset<ll> s;
    
    indexOfMedian = k/2;
    leftLen = 0, rightLen = 0;
    leftSum = 0, rightSum = 0;
    
    forn(i, k) s.insert({A[i], i});
    forn(i, k){
		ll v = (*s.find_by_order(i)).fst;
		if (i < indexOfMedian){
			leftLen++;
			leftSum += v;
		} else if (i > indexOfMedian){
			rightLen++;
			rightSum += v;
		}
	}
	
	//~ DBG(A); DBG(k);
	cout << get_answer(s) << " ";
		
	forsn(i, k, n){
		pair<ll, int> toDelete = *s.find({A[i-k], i-k});
		int indexToDelete = (int) s.order_of_key(toDelete);
		
		update(indexToDelete, toDelete.fst, -1);
		s.erase(toDelete); // Elimino el elemento
		
		// Agrego el nuevo elemento
		pair<ll, int> toAdd = {A[i], i};
		s.insert(toAdd);
		
		// Tengo que chequear la posición de este elemento
		int indexToAdd = (int) s.order_of_key(toAdd);
		update(indexToAdd, toAdd.fst, 1);
		
		// [izquierda] - mediana - [derecha]
		
		if (indexToDelete < indexOfMedian){
			if (indexToAdd >= indexOfMedian){
				// La mediana vieja se fue a la izquierda
				pair<ll, int> oldMedian = *s.find_by_order(indexOfMedian-1);
				leftSum += oldMedian.fst;
			}
			
			if (indexToAdd > indexOfMedian){
				// La mediana nueva viene de la derecha así que le tengo que descontar
				pair<ll, int> newMedian = *s.find_by_order(indexOfMedian);
				rightSum -= newMedian.fst;
			}
		} else if (indexToDelete > indexOfMedian){
			if (indexToAdd <= indexOfMedian){
				// La mediana vieja se fue a la derecha
				pair<ll, int> oldMedian = *s.find_by_order(indexOfMedian+1);
				rightSum += oldMedian.fst;
			}
			
			if (indexToAdd < indexOfMedian){
				// La mediana nueva viene de la izquierda así que le tengo que descontar
				pair<ll, int> newMedian = *s.find_by_order(indexOfMedian);
				leftSum -= newMedian.fst;
			}
		} else {
			if (indexToAdd < indexOfMedian){
				// La mediana nueva viene de la izquierda así que le tengo que descontar
				pair<ll, int> newMedian = *s.find_by_order(indexOfMedian);
				leftSum -= newMedian.fst;
			} else if (indexToAdd > indexOfMedian){
				// La mediana nueva viene de la derecha así que le tengo que descontar
				pair<ll, int> newMedian = *s.find_by_order(indexOfMedian);
				rightSum -= newMedian.fst;
			}
		}
		
		cout << get_answer(s) << " ";
	}
	
	cout << "\n";
	
}
