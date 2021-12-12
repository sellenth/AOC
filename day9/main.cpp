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

void parseInput(string line, vector<int> &input){
    stringstream s_stream(line);
    char c;
    while(s_stream.good()){
        c = s_stream.get();
        input.push_back(c - 48);
    }

    input.pop_back();
}

bool isLowPoint(int x, int y, vector<vector<int>> &cave){
    int currElevation = cave[x][y];
    if (x - 1 >= 0 && cave[x-1][y] <= currElevation){
        return false;
    }
    if (x + 1 < cave.size() && cave[x+1][y] <= currElevation){
        return false;
    }
    if (y - 1 >= 0 && cave[x][y-1] <= currElevation){
        return false;
    }
    if (y + 1 < cave[0].size() && cave[x][y+1] <= currElevation){
        return false;
    }
    return true;
}

int part1()
{
    char filename[] = "./ex.txt";
    //char filename[] = "./input.txt";

    ifstream in(filename);
    vector<vector<int>> cave;

    string line;
    int i = 0;
    while (in.good()){
        cave.push_back({});
        getline(in, line);
        parseInput(line, cave[i]);
        i++;
    }

    int sum = 0;

    for (int i = 0; i < cave.size(); i++){
        for (int j = 0; j < cave[0].size(); j++){
            if (isLowPoint(i, j, cave)){
                sum += cave[i][j] + 1;
            }
        }
    }

    cout << sum << endl;

    return 0;
}

void addAdjacents(int x, int y, vector<vector<int>> &cave, vector<pair<int,int>> &adjacents){
    cave[x][y] = 9;
    if (x - 1 >= 0 && cave[x-1][y] != 9){
        adjacents.push_back({x-1, y});
        cave[x-1][y] = 9;
    }
    if (x + 1 < cave.size() && cave[x+1][y] != 9){
        adjacents.push_back({x+1, y});
        cave[x+1][y] = 9;
    }
    if (y - 1 >= 0 && cave[x][y-1] != 9){
        adjacents.push_back({x, y-1});
        cave[x][y-1] = 9;
    }
    if (y + 1 < cave[0].size() && cave[x][y+1] != 9){
        adjacents.push_back({x, y+1});
        cave[x][y+1] = 9;
    }
    return;
}

void findBasins(vector<vector<int>> &cave, vector<int> &basins){
    vector<pair<int,int>> adjacents;

    for (int i = 0; i < cave.size(); i++){
        for (int j = 0; j < cave[0].size(); j++){
            if (cave[i][j] != 9 && adjacents.empty()){
                basins.push_back(1);
                addAdjacents(i, j, cave, adjacents);
            }
            while (!adjacents.empty()){
                pair<int, int> curr = adjacents.back();
                adjacents.pop_back();
                basins.back() += 1;
                addAdjacents(curr.first, curr.second, cave, adjacents);
            }
        }
    }

}

int part2()
{
    vector<vector<int>> cave;

    {
        //char filename[] = "./ex.txt";
        char filename[] = "./input.txt";

        ifstream in(filename);

        string line;
        int i = 0;
        while (in.good()){
            cave.push_back({});
            getline(in, line);
            parseInput(line, cave[i]);
            i++;
        }
        in.close();
    }

    vector<int> basins;

    findBasins(cave, basins);


    int b1 = 0;
    int b2 = 0;
    int b3 = 0;

    for (auto it = basins.rbegin(); it != basins.rend(); it++){
        if (*it > b1){
            b3 = b2;
            b2 = b1;
            b1 = *it;
        }
        else if (*it > b2){
            b3 = b2;
            b2 = *it;
        }
        else if (*it > b3){
            b3 = *it;
        }
    }

    cout << b1 * b2 * b3 << endl;


    return 0;
}

int main()
{
    //part1();
    part2();
}