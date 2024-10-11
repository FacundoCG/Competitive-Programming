#include <bits/stdc++.h>
using namespace std;

bool canBuy(vector<int> &prices, int money){
    int minimum = INT_MAX;

    for (int i = 1; i < prices.size(); i++) {
        minimum = min(minimum, prices[i]);
    }

    return money >= minimum;
}

int bestDigitToBuy(vector<int> &prices, int price, int start, int end, vector<bool> &used){
    int bestDigit;
    int digitsBought;

    
    if (!used[start]){
        bestDigit = start;
        digitsBought = price/prices[start];
    } else {
        bestDigit = start;
        digitsBought = 0;
    }
    

    for (int i = start+1; i <= end; i++) {
        int bought = price/prices[i];

        if (bought >= digitsBought && !used[i]) {
            digitsBought = bought;
            bestDigit = i;
        }
    }

    return bestDigit;
}

void improveNumber(int &money, vector<int> &prices, int digitToBuy, int digitToSell, map<int, int> &quantities){

   while (quantities[digitToSell] > 0 && money + prices[digitToSell] >= prices[digitToBuy]){
        quantities[digitToSell]--;
        quantities[digitToBuy]++;
        money += prices[digitToSell] - prices[digitToBuy];
   } 
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int v;
    cin >> v;

    vector<int> digitsPrices(10);

    for (int i = 1; i <= 9; i++) {
        int k;
        cin >> k;
        digitsPrices[i] = k;
    }

    bool iCanBuy = canBuy(digitsPrices, v);

    if (!iCanBuy){
        cout << -1 << "\n";
        return 0;
    } 
    
    map<int, int> quantities;
    vector<bool> used(10, false);
    int bestDigit = bestDigitToBuy(digitsPrices, v, 1, 9, used);
    int quantity = v/digitsPrices[bestDigit];
    int leftMoney = v - quantity*digitsPrices[bestDigit];

    used[bestDigit] = true;
    quantities[bestDigit] = quantity;
    
    long long candidate1 = 0;
    long long candidate2 = 0;

    vector<int> digits;

    while(iCanBuy && quantities[bestDigit] > 0){
        // En cada iteración saco un dígito del original. Entonces, sumo la plata correspondiente a ese dígito
        // Chequeo cual sería el mejor dígito para comprar entre los que quedan con mi plata. Si no puedo comprar, salgo del while y vuelvo a agregar el dígito que saqué.
        // Si puedo comprar, elijo lo mejor que esté disponible con mi plata (no puede ser el dígito original) y actualizo dicho cantidad. Me descuento su precio.
        quantities[bestDigit]--;
        leftMoney += digitsPrices[bestDigit];

        int digitToBuy = bestDigitToBuy(digitsPrices, leftMoney, 1, 9, used);
        //cout << "The best digit to buy is " << bestDigitToBuy << endl;

        if (digitsPrices[digitToBuy] > leftMoney){
            quantities[bestDigit]++;
            iCanBuy = false;
        } else {
            if (quantities.find(digitToBuy) == quantities.end()){
                quantities[digitToBuy] = 1;
            } else {
                quantities[digitToBuy]++;
            }

            leftMoney -= digitsPrices[digitToBuy];
        }
    }

    for (const auto &pair : quantities){
        int d = pair.first;

        if (d < bestDigit && leftMoney + digitsPrices[d] >= digitsPrices[bestDigit]){
            improveNumber(leftMoney, digitsPrices, bestDigit, d, quantities);
        } 
    }

    for (const auto &pair : quantities){
        int m = pair.second;
        int d = pair.first;

        while (m > 0){
            digits.push_back(d);
            m--;
        }
    }
    
    sort(digits.begin(), digits.end());
    
    for (int i = 0; i < quantity; i++){
        long long exp = (long long) pow(10, i);
        candidate1 += (long long) exp * bestDigit;
    }

    for (int i = 0; i < digits.size(); i++){
        long long exp = (long long) pow(10, i);
        candidate2 += (long long) exp * digits[i];
    }

    if (candidate1 > candidate2){
        cout << candidate1 << "\n";
    } else {
        cout << candidate2 << "\n";
    }
}
