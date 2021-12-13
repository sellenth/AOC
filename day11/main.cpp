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

int numBlinks = 0;

void incrementNeighbors(int x, int y, vector<vector<int>> &fishTable);

void incrementIfInBounds(int x, int y, vector<vector<int>> &fishTable){
    if (x >= 0 && x < fishTable.size() && y >= 0 && y < fishTable[0].size()){
        if (fishTable[x][y] == 9){
            fishTable[x][y]++;
            incrementNeighbors(x, y, fishTable);
        } else {
            fishTable[x][y]++;
        }

    }
}

void incrementNeighbors(int x, int y, vector<vector<int>> &fishTable){
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (!(i == 0 && j == 0)){
                incrementIfInBounds(x + i, y + j, fishTable);
            }
        }
    }
}

void parseInput(string line, vector<int> &input){
    stringstream s_stream(line);
    while(s_stream.good()){
        input.push_back(s_stream.get() - 48);
    }
    input.pop_back();
}

void dumpTable(vector<vector<int>> &table){
    for (int i = 0; i < table.size(); i++){
        for (int j = 0; j < table[0].size(); j++){
            cout << table[i][j];
        }
        cout << endl;
    }
}

void blinkFish(vector<vector<int>> &table){
    for (int i = 0; i < table.size(); i++){
        for (int j = 0; j < table[0].size(); j++){
            if (table[i][j] > 9){
                table[i][j] = 0;
                numBlinks++;
            }
        }
    }
}

int part1()
{
    char filename[] = "./ex.txt";
    //char filename[] = "./input.txt";

    ifstream in(filename);
    vector<vector<int>> fishTable;

    string line;
    int i = 0;
    while (in.good()){
        fishTable.push_back({});
        getline(in, line);
        parseInput(line, fishTable[i]);
        i++;
    }

    for (int days = 0; days < 100; days++){
        for (int i = 0; i < fishTable.size(); i++){
            for (int j = 0; j < fishTable[0].size(); j++){
                incrementIfInBounds(i, j, fishTable);
            }
        }
        blinkFish(fishTable);
    }

    dumpTable(fishTable);
    cout << "Num blinks: " << numBlinks << endl;
    return 0;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    vector<vector<int>> fishTable;

    string line;
    int i = 0;
    while (in.good()){
        fishTable.push_back({});
        getline(in, line);
        parseInput(line, fishTable[i]);
        i++;
    }

    for (int days = 1; days < 1000; days++){
        for (int i = 0; i < fishTable.size(); i++){
            for (int j = 0; j < fishTable[0].size(); j++){
                incrementIfInBounds(i, j, fishTable);
            }
        }
        int blinkBefore = numBlinks;
        blinkFish(fishTable);
        if (blinkBefore == numBlinks - (fishTable.size() * fishTable[0].size())){
            cout << "synchronized blinks on day: " << days << endl;
            break;
        }
    }

    return 0;
}


int main()
{
    //part1();
    part2();
}