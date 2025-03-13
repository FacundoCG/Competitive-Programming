/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<vector<int> > adjList(1062);
vector<vector<int> > distancesFrom(1062, vector<int>(1062, -1)); 
vector<vector<bool> > visited(1062, vector<bool>(1062, false)); 

map<int, int> mapPrime;

bool isPrime(int n){
    for (int i = 2; i*i <= n; i++){
        if (n % i == 0) return false;
    }
    
    return true;
}

vector<int> digitsOf(int n){
    vector<int> res;
    int firstDigitOfN = n%10;
    int secondDigitOfN = (n/10) % 10;
    int thirdDigitOfN = (n/100) % 10;
    int fourthDigitOfN = (n/1000) % 10;
    res.push_back(firstDigitOfN);
    res.push_back(secondDigitOfN);
    res.push_back(thirdDigitOfN);
    res.push_back(fourthDigitOfN);
    return res;
}

bool differInOneDigit (int n, int m){
    vector<int> digitsN = digitsOf(n);
    vector<int> digitsM = digitsOf(m);
    int differences = 0;
    
    for (int i = 0; i < 4; i++) differences += (digitsN[i] != digitsM[i]);
    return differences <= 1;
} 

vector<int> calculatePrimesUntil(int n){
    vector<int> res;
    
    for (int i = 1000; i <= n; i++){
        if (isPrime(i)) res.push_back(i);
    }
    
    return res;
}

int bfs(int v, int u){
    visited[v][v] = true;
    distancesFrom[v][v] = 0;
    
    queue<int> q;
    q.push(v);
    
    while (!q.empty()){
        int w = q.front();
        q.pop();
        
        for (int i = 0; i < adjList[w].size(); i++){
            int k = adjList[w][i];
            if (!visited[v][k]){
                distancesFrom[v][k] = distancesFrom[v][w] + 1;
                visited[v][k] = true;
                q.push(k);
            }
        }
    }
    
    return distancesFrom[v][u];
}

int main()
{
    vector<int> primes = calculatePrimesUntil(9999); 

    // Now I add the edges between the primes. I add an edge between p1 and p2 if and only if p1 and p2 differ in one digit
    
    for (int i = 0; i < primes.size(); i++){
        mapPrime[primes[i]] = i;
    }
    
    cout << primes.size();
    
    for (int i = 0; i < primes.size(); i++){
        for (int j = i+1; j < primes.size(); j++){
            if (differInOneDigit(primes[i], primes[j])){
                adjList[i].push_back(j);
                adjList[j].push_back(i);
            }
        }
    }
    
    
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++){
        int p1, p2;
        cin >> p1 >> p2;
        
        int v = mapPrime[p1];
        int w = mapPrime[p2];
        
        int res = distancesFrom[v][w]; 
        if (p1 == p2) res = 0;
        if (!visited[v][v]) res = bfs(v, w);
        
        if (res == -1){
            cout << "Impossible\n";
        } else {
            cout << res << "\n";
        }
    }
    
    return 0;
}

