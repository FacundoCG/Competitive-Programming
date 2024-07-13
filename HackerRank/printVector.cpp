#include <bits/stdc++.h>

using namespace std;

void printVector(vector<int> vectorToPrint) {
    int m = vectorToPrint.size();
    cout << "[";

    for (int i = 0; i < vectorToPrint.size(); i++) {
        cout << vectorToPrint[i];
        if (i != m - 1) cout << "," << " ";
    }

    cout << "]" << "\n";
}

int main()
{
   vector<int> vectorSample = {1,2,3};

   printVector(vectorSample);

    return 0;
}
