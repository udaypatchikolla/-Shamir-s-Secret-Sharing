#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
using Big = boost::multiprecision::cpp_int;

Big parseInBase(const string &s, int b) {
    Big x = 0;
    for(char c: s) {
        int d = (isdigit(c) ? c - '0' : toupper(c) - 'A' + 10);
        x = x * b + d;
    }
    return x;
}

Big lagrangeC0(const vector<pair<Big,Big>>& pts) {
    int k = pts.size();
    Big result = 0;
    for(int i = 0; i < k; i++){
        Big xi = pts[i].first;
        Big yi = pts[i].second;
        Big num = 1, den = 1;
        for(int j = 0; j < k; j++){
            if(j == i) continue;
            Big xj = pts[j].first;
            num *= (Big)0 - xj;
            den *= (xi - xj);
        }
        // term = yi * num / den
        result += yi * num / den;
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    json j;
    cin >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];
    vector<pair<Big,Big>> pts;

    for(auto& it : j.items()){
        if(it.key() == "keys") continue;
        Big x = 0;
        x = it.key().to_ulong(); // key is x
        int base = stoi(it.value()["base"].get<string>());
        string val = it.value()["value"].get<string>();
        Big y = parseInBase(val, base);
        pts.emplace_back(x, y);
    }

    sort(pts.begin(), pts.end(), [](auto &a, auto &b){
        return a.first < b.first;
    });

    vector<pair<Big,Big>> firstk(pts.begin(), pts.begin() + k);
    Big secret = lagrangeC0(firstk);
    cout << secret << "\n";
    return 0;
}
