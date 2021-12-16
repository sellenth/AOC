#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

void parseInput(string line, unordered_map<string, char> &rules){
    stringstream s_stream(line);
    string key, value;
    while(s_stream.good()){
        string substr;
        getline(s_stream, key, ' ');
        getline(s_stream, value, ' ');
        getline(s_stream, value);
        rules.emplace(key, value[0]);
    }
}

void stepPolymer(string &polymer, unordered_map<string, string> &rules){
    string newPolymer = "";
    for (int i = 0; i < polymer.size(); i++){
        newPolymer += polymer[i] + rules[polymer.substr(i, 2)];
    }
    polymer = newPolymer;
}

int quantityDifference(string &polymer){
    unordered_map<char, int> counts;

    for (auto &p : polymer){
        if (counts.find(p) == counts.end()){
            counts.emplace(p, 1);
        } else {
            counts[p]++;
        }
    }

    int minQty = -1;
    int maxQty = 1;

    for (auto &c : counts){
        if (c.second > maxQty){
            maxQty = c.second ;
        }
        if (minQty == -1 || c.second < minQty){
            minQty = c.second;
        }
    }

    return maxQty - minQty;
}

void initMaps(unordered_map<string, char> &rules, unordered_map<char, long long> &polymerQty, unordered_map<string, long long> &pairCounts, string &polymer){
    //init polymerQty map
    for (auto &r : rules){
        polymerQty.emplace(r.second, 0);
        pairCounts.emplace(r.first, 0);
    }

    //add polymers in initial string to Qty map
    for (auto &c : polymer){
        polymerQty[c]++;
    }

    for (int i = 0; i < polymer.size() - 1; i++){
        pairCounts[polymer.substr(i, 2)]++;
    }
}

void stepPolymer2(unordered_map<string, char> &rules, unordered_map<char, long long> &polymerQty, unordered_map<string, long long> &pairCounts, string &polymer){
    unordered_map<string, long long> newCounts;


    for (auto &r : rules){
        newCounts.emplace(r.first, 0);
    }

    for (auto &p : pairCounts){
        if (p.second > 0){
            char c1 = p.first[0];
            char c2 = p.first[1];
            char newPolymer = rules[p.first];
            polymerQty[newPolymer] += p.second;
            newCounts[string() + c1 + newPolymer] += p.second;
            newCounts[string() + newPolymer + c2] += p.second;
        }
    }

    pairCounts = newCounts;
}

long long quantityDifference2(unordered_map<char, long long> &sums){
    long long minQty = -1;
    long long maxQty = 1;

    for (auto &c : sums){
        if (c.second > maxQty){
            maxQty = c.second;
        }
        if (minQty == -1 || c.second < minQty){
            minQty = c.second;
        }
    }



    return maxQty - minQty;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    string polymer;
    unordered_map<string, char> rules;
    unordered_map<string, long long> pairCounts;
    unordered_map<char, long long> polymerQty;
    getline(in, polymer);

    string line;
    getline(in, line);
    while (in.good()){
        getline(in, line);
        parseInput(line, rules);
    }

    initMaps(rules, polymerQty, pairCounts, polymer);


    for (int i = 0; i < 40; i++){
        stepPolymer2(rules, polymerQty, pairCounts, polymer);
        cout << "finished step: " << i << endl;
    }    

    cout << "Max-min = " << quantityDifference2(polymerQty) << endl;

    return 0;
}




int main()
{
    //part1();
    part2();
}