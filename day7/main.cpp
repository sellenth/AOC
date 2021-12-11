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
    while(s_stream.good()){
        string substr;
        getline(s_stream, substr, ',');
        input.push_back(stoi(substr));
    }
}

int solvePart1(vector<int> &input){
    sort(input.begin(), input.end());

    int xPos = input[input.size() / 2.0 ];
    int sum = 0;

    for (auto i : input){
        sum += abs(i - xPos);
    }
    
    return sum;
}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    vector<int> positions;

    string line;
    while (in.good()){
        getline(in, line);
        parseInput(line, positions);
    }

    cout << solvePart1(positions) << endl;


    return 0;
}

int solvePart2(vector<int> &input){
    int sum = 0;

    for (auto i : input){
        sum += i;
    }


    int xPos = round(1.0 * sum / input.size() );
    cout << 1.0 * sum / input.size() << endl;;

    sum = 0;
    for (auto i : input){
        int inc = 1;
        for (int j = 0; j < abs(i - xPos); j++){
            sum += inc;
            inc++;
        }
    }
    return sum;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    vector<int> positions;

    string line;
    while (in.good()){
        getline(in, line);
        parseInput(line, positions);
    }

    cout << solvePart2(positions) << endl;


    return 0;
}


int main()
{
    //part1();
    part2();
}