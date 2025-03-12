#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll UNDEFINED = -1;
const int MAX_N = 1e5 + 1;
const ll MOD = 998244353;
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

vector<int> charsOfSubstring(int start, int end, string &t){
	vector<int> charsSubstring(26);
	
	for (int k = start; k <= end; k++){
		int c = t[k] - 'a';
		charsSubstring[c]++;
	}
	
	return charsSubstring;
}

bool checkPalindrome(int start, int end, string &t){
	while (start <= end){
		if (t[start] != t[end]) return false;
		start++; end--;
	}
	
	return true;
}

bool checkPermutations(vector<int> &chars1, vector<int> &chars2){
	forn(i, SIZE(chars1)){
		if (chars1[i] != chars2[i]) return false;
	}
	
	return true;
}

bool Q(vector<int> &chars1, vector<int> &chars2, int sizeOfTheSubstring){ // chars1 has more chars than chars2
	forn(i, SIZE(chars2)) chars1[i] -= chars2[i];
	forn(i, SIZE(chars1)){
		if (chars1[i] < 0) return false;
	}
	
	// I need to know if the resting chars allow me to make a palindrome
	ll oddRepetitions = 0;
	
	forn(i, SIZE(chars1)){
		if (chars1[i] % 2 == 1) oddRepetitions++;
	}

	if (oddRepetitions > 1) return false;
	return (oddRepetitions == 0 && sizeOfTheSubstring % 2 == 0) || (oddRepetitions == 1 && sizeOfTheSubstring % 2 == 1);
}

bool P(int k, string &t){
	int n = SIZE(t);

	// El primer substring va a ser [0, ..., k-1] y el segundo [n-k, n-1]
	// Me queda ver que pasa con el substring [k, n-k-1]
	
	if (k-1 >= n-k){ // Tienen intserccion. Lo que tengo que chequear es si shuffleo uno como me queda el otro
		// Si shuffleo el primer substring tendria los dos siguientes
		// [0, ..., k-1] y [k, ..., n-1] puedo shuflear al primero y al segundo
		// [0, ..., n-k-1] y [n-k, ..., n-1] puedo shuflear al segundo y al primero no
		//int sizeOfTheStringInTheMiddle = (k-1)-(n-k)+1;
		int sizeOfTheStringInTheMiddle = 2*k-n;
		vector<int> chars1 = charsOfSubstring(0, k-1, t); // Puedo shufflear 
		vector<int> chars2 = charsOfSubstring(k, n-1, t); // No puedo ""
		vector<int> chars3 = charsOfSubstring(0, n-k-1, t); // No puedo ""
		vector<int> chars4 = charsOfSubstring(n-k, n-1, t); // Puedo ""
		if (Q(chars1, chars2, sizeOfTheStringInTheMiddle) || Q(chars4, chars3, sizeOfTheStringInTheMiddle)) return true; // Si alguno de los dos shufleos es bueno, entonces es verdad
	} else { // No tienen intersección. Me es indistinto cuál de los dos substrings shuffleo. Solo necesito saber si tienen los mismos caracteres
		vector<int> chars1 = charsOfSubstring(0, k-1, t); // [s[0], ..., s[k-1]]
		vector<int> chars2 = charsOfSubstring(n-k, n-1, t); // [s[n-k], ..., s[n-1]]
		bool arePermutations = checkPermutations(chars1, chars2); // Los dos substrings tienen que ser permutaciones del otro
		bool isPalindrome = checkPalindrome(k, n-k-1, t); // El substring entre el medio de ellos tiene que cumplir que es un palindromo
		if (arePermutations && isPalindrome) return true; 
	}
	
	return false;
}

int leftBinarySearch(int start, int end, string &t){
    int l = start - 1; 
    int r = end + 1; 

    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(!P(mid, t)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return r; // r es el primer elemento que cumple P(X)
}


void solve(string &s){
	string t, reverseT;
	
	int i = 0;
	int j = SIZE(s) - 1;
	
	while (i <= j && s[i] == s[j]){
		i++; j--;
	}
	
	forsn(k, i, j+1) t += s[k];
	
	int res = 0;
	if (SIZE(t) > 0) res = leftBinarySearch(0, SIZE(t)-1, t);
	cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
        
    forn(_, t){
		string s;
		cin >> s;
		solve(s);
	}
}
