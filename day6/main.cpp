#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

void parseInput(string line, long long* fish){
    stringstream s_stream(line);
    while(s_stream.good()){
        string substr;
        getline(s_stream, substr, ',');
        fish[stoi(substr)] += 1;
    }
}

void simulate_fish(long long* &fish1, long long* &fish2){
    for (int i = 8; i >= 0; i--){
        if (i == 0){
            fish2[8] += fish1[i];
            fish2[6] += fish1[i];
        } else {
            fish2[i - 1] = fish1[i];
        }
        fish1[i] = 0;
    }

    long long* tmp = fish1;
    fish1 = fish2;
    fish2 = tmp;
}

void dumpFish(long long* fish){
    for (int i = 0; i < 9; i++){
        cout << fish[i] << ' ';
    }
    cout << endl;
}

long long countFish(long long* fish){
    long long sum = 0;
    for (int i = 0; i < 9; i++){
        sum += fish[i];
    }
    return sum;
}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    ifstream in(filename);
    int days = 256;
    long long* fish1 = new long long[9];
    long long* fish2 = new long long[9];

    for (int i = 0; i < 9; i++){
        fish1[i] = 0;
        fish2[i] = 0;
    }

    string line;
    while (in.good()){
        getline(in, line);
        parseInput(line, fish1);
    }

    dumpFish(fish1);

    for (int i = 0; i < days; i++){
        simulate_fish(fish1, fish2);
        dumpFish(fish1);
    }

    cout << countFish(fish1);


    return 0;
}


int main()
{
    part1();
    //part2();
}