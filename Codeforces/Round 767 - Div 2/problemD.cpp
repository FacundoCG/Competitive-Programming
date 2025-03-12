#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

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

bool isPalindrome(string &s, int start, int end){
    if (start >= end){
        return true;
    }

    return s[start] == s[end] && isPalindrome(s, start+1, end-1);
}

bool existsWordFrom(vector<pair<string, int>> &sortedWords, int start, int end, string &s, int i){
    if (start > end){
        return false;
    }

    int middle = (start + end)/2;

    if (sortedWords[middle].first == s && sortedWords[middle].second >= i){
        return true;
    }

    if (sortedWords[middle].first < s){
        return existsWordFrom(sortedWords, middle+1, end, s, i);
    } else if (sortedWords[middle].first > s){
        return existsWordFrom(sortedWords, start, middle-1, s, i);
    } else {
        if (sortedWords[middle].second < i){
            return existsWordFrom(sortedWords, middle+1, end, s, i);
        } else {
            return existsWordFrom(sortedWords, start, middle-1, s, i);
        }
    }
}

bool existsReverse(vector<pair<string, int>> &sortedWords, string &s, int i){
    string reverse = "";
    int n = sortedWords.size();
    char firstLetter = s[0];
    char secondLetter = s[1];
    
    if (s.size() == 3){
        char thirdLetter = s[2];
        reverse += thirdLetter;
    } 

    reverse += secondLetter;
    reverse += firstLetter;

    return existsWordFrom(sortedWords, 0, n-1, reverse, i);
}

bool existsConcatenationForPalindrome(vector<pair<string, int>> &sortedWords, string &s, int i){
    bool res = existsReverse(sortedWords, s, i);
    int n = sortedWords.size();
    char firstLetter = s[0];
    char secondLetter = s[1];

    if (s.size() == 2){ // I concatenate an string of length 2 with one of length 3
        for (char j = 'a'; j <= 'z'; j++){
            string candidate = "";
            candidate += j;
            candidate += secondLetter;
            candidate += firstLetter;
            res = res || existsWordFrom(sortedWords, 0, n-1, candidate, i);
        }
    } else { // I concatenate an string of length 3 with one of length 2
        string candidate = "";
        candidate += secondLetter;
        candidate += firstLetter;
        res = res || existsWordFrom(sortedWords, 0, n-1, candidate, i);
    }

    return res;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;

    forn(_, t){
        int n;
        cin >> n;

        vector<string> words(n);
        vector<pair<string, int>> sortedWords;
        string res = "NO";

        forn(i, n){
            string s;
            cin >> s;

            words[i] = s;

            if (isPalindrome(s, 0, s.size()-1)){
                res = "YES";
            }

            sortedWords.pb({s, i});
        }

        if (res == "YES"){
            cout << res << "\n";
            continue;
        }

        // I work just with strings >= 2 and not palindromes

        sort(all(sortedWords));

        forn(i, n){
            if (existsConcatenationForPalindrome(sortedWords, words[i], i)){
                res = "YES";
            }
        }

        cout << res << "\n";
    }
}