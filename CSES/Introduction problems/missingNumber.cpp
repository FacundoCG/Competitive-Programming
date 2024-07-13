#include <bits/stdc++.h>

using namespace std;

void differenceSets(set<int> set1, set<int> set2) {
    auto it = set2.begin();

    for (int i = 0; i < set2.size(); i++) {
        
        if (set1.find(*it) == set1.end()) {
            cout << *it << " ";
        }
        it++; 
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;

    set<int> numbersGiven;
    set<int> realNumbers;

    for (int i = 1; i < n+1; i++) {

        if (i != n-1){
            int number;
            cin >> number;
            numbersGiven.insert(number);
        }

        realNumbers.insert(i);
    }

    differenceSets(numbersGiven, realNumbers);
}
