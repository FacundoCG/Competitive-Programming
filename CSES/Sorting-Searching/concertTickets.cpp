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

vector<ll> closestSmallerTicket;
vector<ll> closestBiggerTicket;

int leftBinarySearch(vector<ll> &tickets, int start, int end, ll money){
    int l = start - 1; 
    int r = end + 1; 
    
    while(r - l > 1) { 
        int mid = (l + r) / 2;
        if(tickets[mid] <= money) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return l;
}

void updateChildrenAndParentsOfTickets(ll ticketIndex){
    // I checked that ticketIndex is valid before enter the function
    int n = closestSmallerTicket.size();
    ll sonTicket = closestSmallerTicket[ticketIndex];
    ll parentTicket = closestBiggerTicket[ticketIndex];

    if (sonTicket != -1){
        closestBiggerTicket[sonTicket] = parentTicket;
    }

    if (parentTicket != n){
        closestSmallerTicket[parentTicket] = sonTicket;
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;

    map<ll, ll> repetitionsOfTickets;
    vector<ll> customers(m);
    vector<ll> ticketForTheCustomer(m, UNDEFINED);

    forn(i,n){
        ll ticket;
        cin >> ticket;
        repetitionsOfTickets[ticket]++;
    }

    int k = repetitionsOfTickets.size(); 
    vector<ll> uniqueTickets;

    forn(i,m) cin >> customers[i];

    forn(i,k){
        closestSmallerTicket.pb(i-1);
        closestBiggerTicket.pb(i+1);
    }

    for(auto p : repetitionsOfTickets){
        uniqueTickets.pb(p.first);
    }

    DBG(uniqueTickets);

    forn(i,m){
        ll money = customers[i];
        ll bestTicket = leftBinarySearch(uniqueTickets, 0, k-1, money); // This is an index of the uniqueTickets array

        if (bestTicket != -1 && bestTicket != k){
            ll ticketPrice = uniqueTickets[bestTicket]; // This is the value of the ticket at position bestTicket
            if (uniqueTickets[bestTicket] <= money && repetitionsOfTickets[ticketPrice] > 0){
                repetitionsOfTickets[ticketPrice]--;

                if (repetitionsOfTickets[ticketPrice] == 0){
                    cout << "I update the parent and child for ticket at position: " << bestTicket << endl;
                    updateChildrenAndParentsOfTickets(bestTicket);                
                    DBG(closestSmallerTicket);
                    DBG(closestBiggerTicket);
                }
            } else if (uniqueTickets[bestTicket] <= money && repetitionsOfTickets[ticketPrice] == 0){
                bestTicket = closestSmallerTicket[bestTicket];

                if (i >= 6){
                    cout << "I don't have more repetitions of the ticket" << endl;
                    cout << "I choose the son: " << bestTicket << endl;
                }
                if (bestTicket != -1){
                    ticketPrice = uniqueTickets[bestTicket];
                    //DBG(repetitionsOfTickets[ticketPrice]);
                    repetitionsOfTickets[ticketPrice]--; 


                    if (repetitionsOfTickets[ticketPrice] == 0){
                        updateChildrenAndParentsOfTickets(bestTicket);
                        cout << "I update the parent and child for ticket at position: " << bestTicket << endl;
                        updateChildrenAndParentsOfTickets(bestTicket);                
                        DBG(closestSmallerTicket);
                        DBG(closestBiggerTicket);
                    }
                }
            } else {
                bestTicket = -1;
            }
        } else {
            bestTicket = -1; // This is in case that bestTicket is n
        }

        ticketForTheCustomer[i] = bestTicket;           
    }

    forn(i,m){
        int j = ticketForTheCustomer[i];
        
        if (j != -1){
            cout << uniqueTickets[j] << "\n";
        } else {
            cout << j << "\n";
        }
    }
}