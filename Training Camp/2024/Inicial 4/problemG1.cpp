#include <bits/stdc++.h>
using namespace std;

bool canBuy(vector<long long> &prices, long long money){
    long long minimum = INT_MAX;

    for (long long i = 1; i < prices.size(); i++) {
        minimum = min(minimum, prices[i]);
    }

    return money >= minimum;
}

long long bestDigitToBuy(vector<long long> &prices, long long price, long long start, long long end){
    long long bestDigit = start;
    long long digitsBought = price/prices[start];

    for (long long i = start+1; i <= end; i++) {
        long long bought = price/prices[i];

        if (bought >= digitsBought) {
            digitsBought = bought;
            bestDigit = i;
        }
    }

    return bestDigit;
}

long long biggestNumber(long long money, long long n, long long digit, vector<long long> &prices, vector<long long> &digits){
    long long res = 0;

    if (n == 0){
        long long j = 0;
        for (long long i = 1; i < 10; i++){
            long long m = digits[i];

            while (m > 0){
                long long exp = (long long) pow(10, j);
                res += (long long) exp * i;
                j++;
                m--;
            }
        }

        return res;
    }

    if (digit >= 10){
        return 0;
    }

    for (long long i = 0; i <= n; i++){
        if (i*prices[digit] <= money){
            //cout << "I am with the digit: " << digit << " and I used it: " << i << " times" << "\n";
            long long moneyLeft = money - i*prices[digit];
            int digitsLeft = n-i;
            digits[digit] = i;
            res = max(res, biggestNumber(moneyLeft, digitsLeft, digit+1, prices, digits));
            digits[digit] = 0;
        } else {
            break;
        }
    }

    return res;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    long long v;
    cin >> v;

    vector<long long> digitsPrices(10);

    for (long long i = 1; i <= 9; i++) {
        long long k;
        cin >> k;
        digitsPrices[i] = k;
    }

    bool iCanBuy = canBuy(digitsPrices, v);

    if (!iCanBuy){
        cout << -1 << "\n";
        return 0;
    } 

    vector<long long> digits(10, 0);    
    long long bestDigit = bestDigitToBuy(digitsPrices, v, 1, 9);
    long long n = v/digitsPrices[bestDigit];

    long long res = (long long) biggestNumber(v, n, 1, digitsPrices, digits);

    cout << (long long) res << "\n";
}
