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

vector<pair<ll, ll>> aristasGrafos(vector<vector<ll>>& adj){
    map<pair<ll, ll>, bool> visited;
    vector<pair<ll, ll>> edges;

    int n = adj.size();

    for (int i = 1; i < n; i++){
        vector<ll> neighbors = adj[i];

        for (int j = 0; j < neighbors.size(); j++){
            if (visited.find({adj[i][j], i}) == visited.end()){
                visited[{i, adj[i][j]}] = true;
                edges.pb({i, adj[i][j]});
            }
        }
    }

    return edges;
}

void arbolBFS(ll inicio, vector<vector<ll>> &ady, vector<bool> &visited){
    queue<ll> q;
    q.push(inicio);
    visited[inicio] = true;

    while (!q.empty()){
        ll v = q.front();
        q.pop();

        for (ll u : ady[v]){
            //cout << "Neighbor " << u << " of " << v << endl;
            if (!visited[u]){
                q.push(u);
                visited[u] = true;
                cout << v << " " << u << "\n";
            }
        }
    }
}

void bfsFlags(ll inicio, vector<vector<ll>> &ady, ll flagActual, vector<ll> &flagComponentes, vector<ll> &componente){
    queue<ll> q;
    q.push(inicio);
    flagComponentes[inicio] = flagActual;

    while(!q.empty()){
        ll v = q.front();
        componente.pb(v);
        q.pop();
        for (ll u : ady[v]){
            if (flagComponentes[u] == UNDEFINED){
                flagComponentes[u] = flagActual;
                q.push(u);
            }
        }
    }
}

int main(){
    ll n, m, d;

    cin >> n >> m >> d;

    vector<vector<ll>> ady(n + 1);
    vector<vector<ll>> ady_sin_1(n + 1);

    // Representación del grafo como lista de adyacencia.
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        ady[a].pb(b);
        ady[b].pb(a);

        if(a != 1 && b != 1){
            ady_sin_1[a].pb(b);
            ady_sin_1[b].pb(a);
        }
    }

    // Resuelvo:
    vector<ll> flagComponentes(n+1, UNDEFINED);
    vector<ll> basura;
    bfsFlags(1, ady, 1, flagComponentes, basura);

    // Verifico que originalmente era conexo:
    for(ll i=1; i<=n; i++){
        if(flagComponentes[i] == UNDEFINED){
            // Si no era conexo, imprimo NO.
            cout << "NO" << "\n";
            return 0;
        }
    }

    // Era conexo originalmente.
    flagComponentes.assign(n+1, UNDEFINED);
    ll flagActual = 0;  // También actua como el contador de componentes conexas.

    vector<ll> vecinos1 = ady[1];
    int s = vecinos1.size();
    unordered_map<ll, bool> vecinos1Usados;
    vector<vector<ll>> verticesPorComponente;

    for (int i = 0; i < s; i++){
        vector<long long> componente;
        vecinos1Usados[vecinos1[i]] = false;
        if (flagComponentes[vecinos1[i]] == UNDEFINED){
            //cout << "It is in a different component" << endl;
            bfsFlags(vecinos1[i], ady_sin_1, flagActual, flagComponentes, componente);
            flagActual++;
        }

        if (componente.size() != 0){
            verticesPorComponente.pb(componente);
        }
    }

    if (d > s || d < flagActual){ // Si d es menor a la cantidad de componentes conexas o la cantidad de vecinos de 1 es menor a d, imprimo NO.
        cout << "NO" << endl;
        return 0;
    }

    for (int i = 0; i <= flagActual-1; i++){
        int v = verticesPorComponente[i][0];
        vecinos1Usados[v] = true;
        ady_sin_1[1].pb(v);
        ady_sin_1[v].pb(1);

        /* for (ll v : vecinos1){
            if (flagComponentes[v] == i){
                //cout << "I added the edge: (" << 1 << ", " << v << ")" << endl;
                vecinos1Usados[v] = true;
                ady_sin_1[1].pb(v);
                ady_sin_1[v].pb(1);
                break;
            }
        } */
    }

    d -= flagActual;

    while (d > 0){
        for (auto it = vecinos1Usados.cbegin(); it != vecinos1Usados.cend(); ++it){
            if (!it -> second){ // Si no usé al vecino, lo agrego y resto al d.
                ady_sin_1[1].pb(it->first);
                ady_sin_1[it->first].pb(1);
                d--;

                if (d == 0){
                    break;
                }
            }
        }
    }

    cout << "YES" << "\n";

    vector<bool> visitados(n+1, false);
    arbolBFS(1, ady_sin_1, visitados);
}
