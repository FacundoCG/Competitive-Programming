#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'flippingBits' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER n as parameter.
 */


long binaryToDecimal(long n){
    stack<long> binaryDigits;
    long decimalNumber = 0;

    if (n == 1 || n == 0) return n;

    while (n != 0){
        binaryDigits.push(n%2);
        n /= 10;
    }

    int m = binaryDigits.size();

    for (int i = 0; i < m; i++){
        decimalNumber += binaryDigits.top() * pow(2, m - i - 1);
        binaryDigits.pop();
    }

    return decimalNumber;
}


long decimalToBinary(long n){
    stack<long> binaryDigits;
    long binaryNumber = 0;

    if (n == 1 || n == 0) return n;

    while (n != 0){
        binaryDigits.push(n%2);
        n/=2;
    }

    int m = binaryDigits.size();

    for (int i = 0; i < m; i++){
        binaryNumber += binaryDigits.top() * pow(10, m-i-1);
        binaryDigits.pop();
    }

   return binaryNumber; 
}

int numberOfDigits(long n){
    int result = 0;

    while (n != 0){
        result += 1;
        n /= 10;
    }

    return result;
}


vector<long> vectorOfDigits(long n){
    stack<long> binaryDigits;
    vector<long> vectorDigits(32);

    while (n != 0){
        binaryDigits.push(n%2);
        n /= 10;
    }

    int m = binaryDigits.size();

    while (binaryDigits.size() != 32){
        binaryDigits.push(0);
    }

    for (int i = 31; i >= 0; i--){
        vectorDigits[i] = binaryDigits.top();
        binaryDigits.pop();
    }

    return vectorDigits;
}



long flippingBits(long n) {
    long transformedNumber = 0;
    long newBinaryNumber = 0;
    long binaryNumber = decimalToBinary(n);
    vector<long> binaryDigits = vectorOfDigits(binaryNumber);

    for (int i=0; i<binaryDigits.size(); i++){
        if (binaryDigits[i] == 1) binaryDigits[i] = 0;
        else {binaryDigits[i] = 1;}
    }

    for (int i=0; i<binaryDigits.size(); i++){
        newBinaryNumber += binaryDigits[i] * pow(2, i);
    }

    return newBinaryNumber;
}

int main()
{
    int q;
    cin >> q;

    for (int i = 0; i < q; i++){
        long n;
        cin >> n;

        cout << flippingBits(n) << endl;
    }

    return 0;
}