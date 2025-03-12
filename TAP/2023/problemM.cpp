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

#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define all(c) (c).begin(),(c).end()

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl

#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)

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

template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

// ############################################################### //

int main()
{
    ld n, t;
    cin >> n >> t;

    vector<ld> priorityFiles;
    vector<ld> nonPriorityFiles;

    ld timeInSeconds = 0;

    forn(i,n){
        ld size;
        char c;

        cin >> c >> size;

        if (c == 'P'){
            priorityFiles.push_back(size);
        } else {
            nonPriorityFiles.push_back(size);
        }
    }

    sort(all(priorityFiles));
    sort(all(nonPriorityFiles));

    int m = priorityFiles.size();
    int k = nonPriorityFiles.size();
    int copyM = m;
    int copyK = k;

    int i = 0; 
    int j = 0;

    while (i < m || j < k){
        ld requiredTime = 0;

        if (i < m && j < k){
            ld speedForPF = (ld) t*75/(100*copyM);
            ld speedForNPF = (ld) t*25/(100*copyK);

            ld timeForMinPF = (ld) priorityFiles[i] / speedForPF;
            ld timeForMinNPF = (ld) nonPriorityFiles[j] / speedForNPF;
            requiredTime = min(timeForMinPF, timeForMinNPF);

            if (timeForMinPF > timeForMinNPF){
                copyK--;
                j++;
            } else {
                i++;
                copyM--;
            }

            for (int h = i; h < m; h++){
                ld downloaded = (ld) speedForPF * requiredTime;
                priorityFiles[h] -= (ld) downloaded;
            }

            for (int h = j; h < k; h++){
                ld downloaded = (ld) speedForNPF * requiredTime;
                nonPriorityFiles[h] -= (ld) downloaded;
            }

        } else if (i < m){
            ld speed = (ld) t/copyM;
            requiredTime = (ld) priorityFiles[i]/speed;
            i++;
            copyM--;

            for (int h = i; h < m; h++){
                ld downloaded = (ld) speed * requiredTime;
                priorityFiles[h] -= (ld) downloaded;
            }
        } else {
            ld speed = (ld) t/copyK;
            requiredTime = (ld) nonPriorityFiles[j]/speed;
            j++;
            copyK--;

            for (int h = j; h < k; h++) {
                ld downloaded = (ld) speed * requiredTime;
                nonPriorityFiles[h] -= downloaded;
            }
        }

        timeInSeconds += requiredTime;
    }

    cout << setprecision(numeric_limits<long double>::digits10 + 1);
    cout << timeInSeconds << "\n";
}