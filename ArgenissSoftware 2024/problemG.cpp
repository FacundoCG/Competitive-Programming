#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>> vectorDe9;
typedef vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>> vectorDe8;
typedef vector<vector<vector<vector<vector<vector<vector<ll>>>>>>> vectorDe7;
typedef vector<vector<vector<vector<vector<vector<ll>>>>>> vectorDe6;
typedef vector<vector<vector<vector<vector<ll>>>>> vectorDe5;
typedef vector<vector<vector<vector<ll>>>> vectorDe4;
typedef vector<vector<vector<ll>>> vectorDe3;
typedef vector<vector<ll>> vectorDe2;


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


// Rango de int: -2*10^9 <= x <= 2*10^9
// Rango de long long: -9*10^18 <= x <= 9*10^18

// ############################################################### //

ll countForNinethNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9){
    if (n9 != 0){
        return memo[n1][n2][n3][n4][n5][n6][n7][n8][n9];
    }

    ll res = 0;

    forn(i,4){
        res += (ll) memo[n1][n2][n3][n4][n5][n6][n7][n8][i];
    }

    return res;
}

ll countForEighthNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8){
    int n9 = aCard[2][2] - '0';

    if (n8 != 0){
        return countForNinethNumber(aCard, memo, n1, n2, n3, n4, n5, n6, n7, n8, n9);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForNinethNumber(aCard, memo, n1, n2, n3, n4, n5, n6, n7, i, n9);
    }

    return res;
}

ll countForSeventhNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3, int n4, int n5, int n6, int n7){
    int n8 = aCard[2][1] - '0';

    if (n7 != 0){
        return countForEighthNumber(aCard, memo, n1, n2, n3, n4, n5, n6, n7, n8);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForEighthNumber(aCard, memo, n1, n2, n3, n4, n5, n6, i, n8);
    }

    return res;
}

ll countForSixthNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3, int n4, int n5, int n6){
    int n7 = aCard[2][0] - '0';

    if (n6 != 0){
        return countForSeventhNumber(aCard, memo, n1, n2, n3, n4, n5, n6, n7);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForSeventhNumber(aCard, memo, n1, n2, n3, n4, n5, i, n7);
    }

    return res;
}

ll countForFifthNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3, int n4, int n5){
    int n6 = aCard[1][2] - '0';

    if (n5 != 0){
        return countForSixthNumber(aCard, memo, n1, n2, n3, n4, n5, n6);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForSixthNumber(aCard, memo, n1, n2, n3, n4, i, n6);
    }

    return res;
}

ll countForFourthNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3, int n4){
    int n5 = aCard[1][1] - '0';

    if (n4 != 0){
        return countForFifthNumber(aCard, memo, n1, n2, n3, n4, n5);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForFifthNumber(aCard, memo, n1, n2, n3, i, n5);
    }

    return res;
}

ll countForThirdNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2, int n3){
    int n4 = aCard[1][0] - '0';

    if (n3 != 0){
        return countForFourthNumber(aCard, memo, n1, n2, n3, n4);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForFourthNumber(aCard, memo, n1, n2, i, n4);
    }

    return res;
}

ll countForSecondNumber(vector<string> &aCard, vectorDe9 &memo, int n1, int n2){
    int n3 = aCard[0][2] - '0';

    if (n2 != 0){
        return countForThirdNumber(aCard, memo, n1, n2, n3);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForThirdNumber(aCard, memo, n1, i, n3);
    }

    return res;
}

ll countForFirstNumber(vector<string> &aCard, vectorDe9 &memo, int n1){
    int n2 = aCard[0][1] - '0';

    if (n1 != 0){
        return countForSecondNumber(aCard, memo, n1, n2);
    }

    ll res = 0;

    forn(i,4){
        res += (ll) countForSecondNumber(aCard, memo, i, n2);
    }

    return res;
}

ll countCards(vector<string> &aCard, vectorDe9 &memo){
    int n1 = aCard[0][0] - '0';

    return countForFirstNumber(aCard, memo, n1);
}

void updateMemoForCard(int i, int j, vector<string> &map, vectorDe9 &memo){
    int firstNumber = map[i][j] - '0';
    int secondNumber = map[i][j+1] - '0';
    int thirdNumber = map[i][j+2] - '0';
    int fourthNumber = map[i+1][j] - '0';
    int fifthNumber = map[i+1][j+1] - '0';
    int sixthNumber = map[i+1][j+2] - '0';
    int seventhNumber = map[i+2][j] - '0';
    int eightNumber = map[i+2][j+1] - '0';
    int ninethNumber = map[i+2][j+2] - '0';

    memo[firstNumber][secondNumber][thirdNumber][fourthNumber][fifthNumber][sixthNumber][seventhNumber][eightNumber][ninethNumber]++;
}

void calculateMemo(vector<string> &map, vectorDe9 &memo){
    forn(i, map.size()-2){
        forn(j,map[0].size()-2){
            updateMemoForCard(i, j, map, memo);
        }
    }
}

void deleteMemoForCard(int i, int j, vector<string> &map, vectorDe9 &memo){
    int firstNumber = map[i][j] - '0';
    int secondNumber = map[i][j+1] - '0';
    int thirdNumber = map[i][j+2] - '0';
    int fourthNumber = map[i+1][j] - '0';
    int fifthNumber = map[i+1][j+1] - '0';
    int sixthNumber = map[i+1][j+2] - '0';
    int seventhNumber = map[i+2][j] - '0';
    int eightNumber = map[i+2][j+1] - '0';
    int ninethNumber = map[i+2][j+2] - '0';

    memo[firstNumber][secondNumber][thirdNumber][fourthNumber][fifthNumber][sixthNumber][seventhNumber][eightNumber][ninethNumber] = 0;
}

void cleanMemo(vector<string> &map, vectorDe9 &memo){
    forn(i, map.size()-2){
        forn(j,map[0].size()-2){
            deleteMemoForCard(i, j, map, memo);
        }
    }
}

string rowOf0s (int m){
    string res = "";

    forn(i,m){
        res += '0';
    }

    return res;
}

vector<string> rotateCardRight(vector<string> &cardOriginal){
    vector<string> rotatedCard = {"___", "___", "___"};

    rotatedCard[0][0] = cardOriginal[2][0];
    rotatedCard[0][1] = cardOriginal[1][0];
    rotatedCard[0][2] = cardOriginal[0][0];
    rotatedCard[1][0] = cardOriginal[2][1];
    rotatedCard[1][1] = cardOriginal[1][1];
    rotatedCard[1][2] = cardOriginal[0][1];
    rotatedCard[2][0] = cardOriginal[2][2];
    rotatedCard[2][1] = cardOriginal[1][2];
    rotatedCard[2][2] = cardOriginal[0][2];

    return rotatedCard;
}

vector<string> buildCard(vector<string> &aCard){
    vector<string> res;

    int n = aCard.size();
    int m = aCard[0].size();

    res.pb(rowOf0s(m+4));
    res.pb(rowOf0s(m+4));

    forn(i,n){
        string s = "00" + aCard[i] + "00";
        res.pb(s);
    }

    res.pb(rowOf0s(m+4));
    res.pb(rowOf0s(m+4));

    return res;
}

void resetMemoHelper(vector<string> &card, vectorDe9 &memo){
    vector<string> newCard = buildCard(card); 
    cleanMemo(newCard, memo);
}

bool existsPatron(vector<string> &card, vectorDe9 &specialMemo){
    int firstNumber = card[0][0] - '0';
    int secondNumber = card[0][1] - '0';
    int thirdNumber = card[0][2] - '0';
    int fourthNumber = card[1][0] - '0';
    int fifthNumber = card[1][1] - '0';
    int sixthNumber = card[1][2] - '0';
    int seventhNumber = card[2][0] - '0';
    int eightNumber = card[2][1] - '0';
    int ninethNumber = card[2][2] - '0';

    return specialMemo[firstNumber][secondNumber][thirdNumber][fourthNumber][fifthNumber][sixthNumber][seventhNumber][eightNumber][ninethNumber] != 0;
}

bool areEquivalent(vector<string> &card1, vector<string> &card2, vectorDe9 &specialMemo){
    vector<string> newCard = buildCard(card1);
    calculateMemo(newCard, specialMemo);
    return existsPatron(card2, specialMemo);
}

bool isSamePatron(int i, int j, int w, int z, vector<string> &card1, vector<string> &card2){
    bool res = true;

    int firstNumberC1 = card1[i][j] - '0';
    int secondNumberC1 = card1[i][j+1] - '0';
    int thirdNumberC1 = card1[i][j+2] - '0';
    int fourthNumberC1 = card1[i+1][j] - '0';
    int fifthNumberC1 = card1[i+1][j+1] - '0';
    int sixthNumberC1 = card1[i+1][j+2] - '0';
    int seventhNumberC1 = card1[i+2][j] - '0';
    int eightNumberC1 = card1[i+2][j+1] - '0';
    int ninethNumberC1 = card1[i+2][j+2] - '0';

    int firstNumberC2 = card2[w][z] - '0';
    int secondNumberC2 = card2[w][z+1] - '0';
    int thirdNumberC2 = card2[w][z+2] - '0';
    int fourthNumberC2 = card2[w+1][z] - '0';
    int fifthNumberC2 = card2[w+1][z+1] - '0';
    int sixthNumberC2 = card2[w+1][z+2] - '0';
    int seventhNumberC2 = card2[w+2][z] - '0';
    int eightNumberC2 = card2[w+2][z+1] - '0';
    int ninethNumberC2 = card2[w+2][z+2] - '0';

    if (firstNumberC2 != firstNumberC1){
        //cout << "False por desigualdad1w" << endl;
        res = false;
    }

    if (secondNumberC2 != secondNumberC1){
        //cout << "False por desigualdad2" << endl;
        res = false;
    }

    if (thirdNumberC1 != thirdNumberC2){
        //cout << "False por desigualdad3" << endl;
        res = false;
    }

    if (fourthNumberC1 != fourthNumberC2){
        //cout << "False por desigualdad4" << endl;
        res = false;
    }

    if (fifthNumberC1 != fifthNumberC2){
        //cout << "False por desigualdad5" << endl;
        res = false;
    }

    if (sixthNumberC1 != sixthNumberC2){
        //cout << "False por desigualdad6" << endl;
        res = false;
    }

    if (seventhNumberC1 != seventhNumberC2){
        //cout << "False por desigualdad7" << endl;
        res = false;
    }

    if (eightNumberC1 != eightNumberC2){
        //cout << "False por desigualdad8" << endl;
        res = false;
    }

    if (ninethNumberC1 != ninethNumberC2){
        //cout << "False por desigualdad9" << endl;
        res = false;
    }

    return res;
}

bool isValidPattern(int i, int j, int w, int z, vector<string> &card1, vector<string> &card2){
    bool res = true;

    forn(a, 7){
        forn(b, 7){
            if (!((a == i || a == i+1 || a == i+2) && (b == j || b == j+1 || b == j+2))){
                res = res && (card1[a][b] == '0');
            }
        }
    }

    forn (a, 7){
        forn(b,7){
            if (!((a == w || a == w+1 || a == w+2) && (b == z || b == z+1 || b == z+2))){
                res = res && (card2[a][b] == '0');
            }
        }
    }

    return res;
}

bool areEquivalent2(vector<string> &card1, vector<string> &card2){
    bool res = false;

    vector<string> newCard1 = buildCard(card1);
    vector<string> newCard2 = buildCard(card2);

    forn(i, 5){
        forn(j,5){
            forn(w, 5){
                forn(z,5){
                    res = res || (isSamePatron(i, j, w, z, newCard1, newCard2) && isValidPattern(i, j, w, z, newCard1, newCard2));
                }
            }
        }
    } 

    return res;
}

void solveForCard(vector<string> &card, vectorDe9 &memo, vectorDe9 &memoHelper, vector<string> &map){
    vector<string> card180 = rotateCardRight(card);
    vector<string> card270 = rotateCardRight(card180);
    vector<string> card0 = rotateCardRight(card270);    

    ll res90 = countCards(card, memo);
    ll res180 = countCards(card180, memo);
    ll res270 = countCards(card270, memo);
    ll res0 = countCards(card0, memo);

    if (areEquivalent2(card, card0)){
        res0 = 0;
    }

    if (areEquivalent2(card, card180)){
        res180 = 0;
    }

    if (areEquivalent2(card, card270)){
        res270 = 0;
    }

    if (areEquivalent2(card180, card270)){
        res270 = 0;
    }

    if (areEquivalent2(card180, card0)){
        res0 = 0;
    }

    if (areEquivalent2(card0, card270)){
        res0 = 0;
    }

    /* DBG(res90);
    DBG(res180);
    DBG(res270);
    DBG(res0); */

    ll res = (ll) res90 + res270 + res180 + res0;
    cout << res << "\n";
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m, q;
    cin >> n >> m;

    vector<string> map;
    vectorDe9 memo(4, vectorDe8(4, vectorDe7(4, vectorDe6(4, vectorDe5(4, vectorDe4(4, vectorDe3(4, vectorDe2(4, vector<ll>(4,0)))))))));
    vectorDe9 memoHelper(4, vectorDe8(4, vectorDe7(4, vectorDe6(4, vectorDe5(4, vectorDe4(4, vectorDe3(4, vectorDe2(4, vector<ll>(4,0)))))))));
    
    map.pb(rowOf0s(m+4));
    map.pb(rowOf0s(m+4));

    forn(i,n){
        string s;
        cin >> s;
        s = "00" + s + "00";
        map.pb(s);
    }

    map.pb(rowOf0s(m+4));
    map.pb(rowOf0s(m+4));

    calculateMemo(map, memo);

    cin >> q;

    forn(_,q){
        vector<string> card90;

        forn(_,3){
            string s;
            cin >> s;
            card90.pb(s);
        }

        solveForCard(card90, memo, memoHelper, map);
    }
}