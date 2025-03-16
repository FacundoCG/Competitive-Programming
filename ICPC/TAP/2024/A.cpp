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

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()
#define pb push_back

#define DBG(x) cerr << #x << " = " << (x) << endl

# define forn(i,n) for (int i=0; i<(int)(n);i++)
# define forsn(i,s,n) for (int i=(s); i <(int)(n); i++)
#define RAYA cerr << "-----------------" << endl

template <typename T>
ostream & operator << (ostream &os, const vector<T> &v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

map<int, set<int>> restrictions;
map<int, set<int>> isARestrictionOf;
map<int, pair<int, int>> positionOnBoard;
vector<vector<int>> board(3, vector<int>(3, 0));

int undefinedRes(int player){
    if (player == 1){
        return -2;
    }

    return 2;
}

bool sameRowEqual(int row, int column){
    return board[row][0] == board[row][1] && board[row][1] == board[row][2];
}

bool sameColumnEqual(int row, int column){
    return board[0][column] == board[1][column] && board[1][column] == board[2][column];
}

bool sameDiagonals(int row, int column){
    bool option1 = board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2];
    bool option2 = board[0][2] != 0 && board[0][2] == board[1][1] && board[2][0] == board[1][1];

    return option1 || option2;
}

bool iWin(int player, int row, int column){
    bool res = sameRowEqual(row, column) || sameColumnEqual(row, column) || sameDiagonals(row, column);
    return res;
}

int playTicTacToe(int depth, int player){
    if (depth == 10){ // If I played all the cells and there isn't a winner, it is a tie
        return 0;
    }

    int res = undefinedRes(player); // The undefined res for the player

    forsn(i, 1, 10){
        int row = positionOnBoard[i].first;
        int col = positionOnBoard[i].second;

        if (restrictions[i].empty() && board[row][col] == 0){ // If I can play this move because it is legal and the cell is empty
            board[row][col] = player; // I update the board

            if (iWin(player, row, col)){ // If I win when I play this move, I update res and finish the game
                board[row][col] = 0;

                if (player == 1){
                    res = 1;
                } else {
                    res = -1;
                }

                break;
            }

            vector<int> eliminatedRestrictions;
            // I eliminate the lastPlay as restriction of some cells
            for (auto j : isARestrictionOf[i]){
                eliminatedRestrictions.pb(j);
                restrictions[j].erase(i);
            }

            // If I am here, it means that the game can be continued
            if (player == 1){
                res = max(res, playTicTacToe(depth+1, player+1));
            } else {
                res = min(res, playTicTacToe(depth+1, player-1));
            }

            for (auto j : eliminatedRestrictions){
                restrictions[j].insert(i);
            }

            board[row][col] = 0; // I clean the board
        }
    }

    if (res == 2 || res == -2){ // If my value is still undefined, it means that I can't play any move
        res = 0; // Then, it is a tie
    }

    return res;
}

int main()
{
    int n;
    cin >> n;

    forsn(i, 1, 10){ // Originally, I don't have any restrictions
        restrictions[i] = {};
    }

    int k = 1;
    forn(i, 3){
        forn(j, 3){
            positionOnBoard[k] = {i, j};
            k++;
        }
    }

    // Now I read the restrictions of the game
    forn(i, n){
        int a, b;
        cin >> a >> b;
        restrictions[b].insert(a);
        isARestrictionOf[a].insert(b);
    }

    int res = playTicTacToe(1, 1);
    string winner = "E";

    if (res == 1){
        winner = "X";
    } else if (res == -1){
        winner = "O";
    }

    cout << winner << "\n";
}
