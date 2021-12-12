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

int part1()
{
    char filename[] = "./ex.txt";
    //char filename[] = "./input.txt";

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



    return 0;
}



int main()
{
    part1();
    //part2();
}