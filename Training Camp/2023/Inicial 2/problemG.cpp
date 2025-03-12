#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> shape;

const ll UNDEFINED = -1;

void printSet(multiset<shape, bool(*)(shape, shape)> &s){
    cout << "{";

    for (auto p : s){
        cout << " (" << p.first << ", " << p.second << ") ";
    }

    cout << "}" << "\n";
}

bool sortByWidth(shape a, shape b){
    // This functions tells you if the area of a is bigger than b. In case of tie, I check if a is widther than b.
    ll heightA = a.first;
    ll widthA = a.second;
    ll heightB = b.first;
    ll widthB = b.second;

    ll areaA = (ll) heightA * widthA;
    ll areaB = (ll) heightB * widthB;

    if (areaA > areaB){
        return true;
    } else if (areaA < areaB){
        return false;
    }

    if (widthA > widthB){
        return true;
    } 

    return false;
}

bool sortByHeight(shape a, shape b){
    // This functions tells you if the area of a is bigger than b. In case of tie, I check if a is higher than b.
    ll heightA = a.first;
    ll widthA = a.second;
    ll heightB = b.first;
    ll widthB = b.second;

    ll areaA = (ll) heightA * widthA;
    ll areaB = (ll) heightB * widthB;

    if (areaA > areaB){
        return true;
    } else if (areaA < areaB){
        return false;
    }

    if (heightA > heightB){
        return true;
    }

    return false;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    ll w, h, n;
    cin >> w >> h >> n;

    multiset<shape, bool(*)(shape, shape)> piecesSortedByHeight(sortByHeight);
    multiset<shape, bool(*)(shape, shape)> piecesSortedByWidth(sortByWidth);
    piecesSortedByHeight.insert({w,h});
    piecesSortedByWidth.insert({w,h});

    for (int i = 0; i < n; i++) {
        char cut;
        ll z;
        cin >> cut >> z;

        shape bestShape = *piecesSortedByHeight.begin();
        ll res = (ll) bestShape.first * bestShape.second;

        printSet(piecesSortedByHeight);

        if (cut == 'H'){
            for (auto piece : piecesSortedByHeight){
                ll width = piece.first;
                ll height = piece.second;

                if (height > z){
                    ll newHeight1 = z;
                    ll newHeight2 = height - z;
                    res = (ll) width * max(newHeight1, newHeight2);
                    shape newShape1 = {width, newHeight1};
                    shape newShape2 = {width, newHeight2};
                    piecesSortedByHeight.erase(piece);
                    piecesSortedByWidth.erase(piece);
                    piecesSortedByHeight.insert(newShape1);
                    piecesSortedByHeight.insert(newShape2);
                    piecesSortedByWidth.insert(newShape1);
                    piecesSortedByWidth.insert(newShape2);
                    break;
                }
            }
        } else {
            for (auto piece : piecesSortedByWidth){
                ll width = piece.first;
                ll height = piece.second;

                if (width > z){
                    ll newWidth1 = z;
                    ll newWidth2 = width - z;
                    res = (ll) height * max(newWidth1, newWidth2);
                    shape newShape1 = {newWidth1, height};
                    shape newShape2 = {newWidth2, height};
                    piecesSortedByHeight.erase(piece);
                    piecesSortedByWidth.erase(piece);
                    piecesSortedByHeight.insert(newShape1);
                    piecesSortedByHeight.insert(newShape2);
                    piecesSortedByWidth.insert(newShape1);
                    piecesSortedByWidth.insert(newShape2);
                    break;
                }
            }
        }
        
        cout << res << "\n";
    }
};
