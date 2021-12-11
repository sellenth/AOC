#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <math.h>

using namespace std;

void parseInput(string line, vector<string> &input){
    stringstream s_stream(line);
    while(s_stream.good()){
        string substr;
        getline(s_stream, substr, ' ');
        sort(substr.begin(), substr.end());
        input.push_back(substr);
    }
}

int solveLineP1(vector<string> &line){
    vector<string> ref;
    for (int i = 0; i < 10; i++){
        ref.push_back("");
    }

    for(int i = 0; i < 10; i++){
        auto &ex = line[i];
        switch(ex.length()){
            case 2:
                ref[1] = ex;
                break;
            case 3:
                ref[7] = ex;
                break;
            case 4:
                ref[4] = ex;
                break;
            case 7:
                ref[8] = ex;
                break;
        }
    }

    int numUniques = 0;

    for(int i = 0; i < 4; i++){
        auto &ex = line[11 + i];
        int l = ex.length();

        if (l == 2 || l == 3 || l == 4 || l == 7){
            numUniques++;
        }
    }

    return numUniques;
}

int solvePart1(vector<vector<string>> &input){
    int sum = 0;
    for (auto &i : input){
        sum += solveLineP1(i);
    }
    return sum;
}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    vector<vector<string>> in_data;

    string line;
    int i = 0;
    while (in.good()){
        in_data.push_back({});
        getline(in, line);
        parseInput(line, in_data[i]);
        i++;
    }

    cout << solvePart1(in_data) << endl;


    return 0;
}

bool containsRightLine(string &ex, string &rl){
    bool hasAllComponents = true;

    for (auto &c : rl){
        if (ex.find(c) == string::npos){
            hasAllComponents = false;
        }
    }

    return hasAllComponents;
}

bool containsUpperLeftL(string &ex, string &ull){
    bool hasAllComponents = true;

    for (auto &c : ull){
        if (ex.find(c) == string::npos){
            hasAllComponents = false;
        }
    }

    return hasAllComponents;
}

int solveLineP2(vector<string> &line){
    vector<string> ref;
    for (int i = 0; i < 10; i++){
        ref.push_back("");
    }

    for(int i = 0; i < 10; i++){
        auto &ex = line[i];
        switch(ex.length()){
            case 2:
                ref[1] = ex;
                break;
            case 3:
                ref[7] = ex;
                break;
            case 4:
                ref[4] = ex;
                break;
            case 7:
                ref[8] = ex;
                break;
        }
    }

    string rightLine = ref[1];

    string upperLeftL;
    for (auto &c : ref[4]){
        if (ref[1].find(c) == string::npos){
            upperLeftL.push_back(c);
        }
    }

    string topLine;
    for (auto &c : ref[7]){
        if (ref[1].find(c) == string::npos){
            topLine.push_back(c);
        }
    }

    for(int i = 0; i < 10; i++){
        auto &ex = line[i];
        switch(ex.length()){
            case 5:
                if( containsRightLine(ex, rightLine) ){
                    ref[3] = ex;
                } else if (containsUpperLeftL( ex, upperLeftL) ){
                    ref[5] = ex;
                } else {
                    ref[2] = ex;
                }
                break;
            case 6:
                if ( containsUpperLeftL(ex, upperLeftL) ) {
                    if ( containsRightLine(ex, rightLine) ) {
                        ref[9] = ex;
                    } else {
                        ref[6] = ex;
                    }
                } else {
                    ref[0] = ex;
                }
                break;
        }
    }

    int sum = 0;

    for(int i = 0; i < 4; i++){
        int currVal = 0;
        auto &ex = line[11 + i];

        for (int j = 0; j < 10; j++){
            if (ex == ref[j]){
                currVal += j * pow(10, 3 - i);
            }
        }

        sum += currVal;
    }

    return sum;
}

int solvePart2(vector<vector<string>> &input){
    int sum = 0;
    for (auto &i : input){
        sum += solveLineP2(i);
    }
    return sum;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    vector<vector<string>> in_data;

    string line;
    int i = 0;
    while (in.good()){
        in_data.push_back({});
        getline(in, line);
        parseInput(line, in_data[i]);
        i++;
    }

    cout << solvePart2(in_data) << endl;


    return 0;
}


int main()
{
    //part1();
    part2();
}