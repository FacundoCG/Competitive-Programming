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

// ############################################################### //

// solve(3, 3, 2, 1, 1, 3)
int solve(int card1, int card2, int a1, int b1, int a2, int b2) {
    int res = 0;
    int grupitos1A = card1/a1;
    int grupitos1B = card2/b1;
    int j = min(grupitos1A, grupitos1B);

    forn(i, j+1){
        int groups = i;
        int cards1Left = card1 - i*a1;
        int cards2Left = card2 - i*b1;

        int grupitos2A = cards1Left/a2;
        int grupitos2B = cards2Left/b2;
        groups += min(grupitos2A, grupitos2B);

        int rest = abs(grupitos2A - grupitos2B);

        int unusedCards1 = cards1Left - grupitos2A*a2;
        int unusedCards2 = cards2Left - grupitos2B*b2;

        if (grupitos2A < grupitos2B){
            unusedCards2 += rest*b2;
        } else {
            unusedCards1 += rest*a2;
        }

        if (groups + unusedCards1/5 + unusedCards2/5 > res){
            res = groups + unusedCards1/5 + unusedCards2/5;
        }
    }

    return res;
}


int main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> numberOfCardsMod5(5,0);

    forn(i,n){
        int card;
        cin >> card;
        numberOfCardsMod5[card%5]++;
    }

    // Las cartas pueden ser de resto: 0, 1, 2, 3, o 4.
    int res = numberOfCardsMod5[0]; // Ya no tengo más cartas que sean divisibles por 5 (resto 0)
    bool meSobranResto1 = true;
    bool meSobranResto2 = true;

    // Yo voy a intentar minimizar el tamaño de los grupos para poder tener más cartas disponibles y armar más grupos
    if (numberOfCardsMod5[1] > numberOfCardsMod5[4]) {
        res += numberOfCardsMod5[4];
        numberOfCardsMod5[1] -= numberOfCardsMod5[4];
        // Ya no tengo más cartas con resto 4 para usar
    } else {
        res += numberOfCardsMod5[1];
        numberOfCardsMod5[4] -= numberOfCardsMod5[1];
        meSobranResto1 = false;
        // Ya no tengo más cartas con resto 1 para usar
    }

    if (numberOfCardsMod5[2] > numberOfCardsMod5[3]) {
        res += numberOfCardsMod5[3];
        numberOfCardsMod5[2] -= numberOfCardsMod5[3];
        // Ya no tengo más cartas con resto 3 para usar
    } else {
        res += numberOfCardsMod5[2];
        numberOfCardsMod5[3] -= numberOfCardsMod5[2];
        meSobranResto2 = false;
        // Ya no tengo más cartas con resto 2 para usar
    }

    //cout << "Res is now" << res << endl;

    // En esta etapa solo deberían quedarme 2 tipos de cartas: (1-2), (1-3), (4-2), (4-3)
    // Combinaciones (1-2): (1 R1 + 2R2) o (3R1 + 1R2)
    // Combinaciones (1-3): (2 R1 + 1R3) o (1R1 + 3R3)
    // Combinaciones (4-2): (2 R4 + 1R2) o (1 R4 + 3R2)
    // Combinaciones (4-3): (3 R4 + 1R3) o (1 R4 + 2R3)

    if (meSobranResto1 && meSobranResto2){
        //cout << "Entre a resto 1 y 2" << endl;
        res += solve(numberOfCardsMod5[1], numberOfCardsMod5[2], 1, 2, 3, 1);        
    } else if (!meSobranResto1 && !meSobranResto2){
        //cout << "Entre a resto 4 y 3" << endl;
        res += solve(numberOfCardsMod5[4], numberOfCardsMod5[3], 3, 1, 1, 2);
    } else if (meSobranResto1 && !meSobranResto2){
        //cout << "Entre a resto 1 y 3" << endl;
        res += solve(numberOfCardsMod5[1], numberOfCardsMod5[3], 2, 1, 1, 3);
    } else if (!meSobranResto1 && meSobranResto2){
        //cout << "Entre a resto 4 y 2" << endl;
        res += solve(numberOfCardsMod5[4], numberOfCardsMod5[2], 2, 1, 1, 3);
    }

    cout << res << "\n";
}