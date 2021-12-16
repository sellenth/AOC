#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

#if 0
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

class Solution {

public:
    vector<vector<int>> map;
    vector<vector<int>> bestScores;

    void parseInput(){
        ifstream in(FILENAME);

        string line;
        while (in.good()){
            map.push_back({});
            getline(in, line);

            stringstream s_stream(line);
            while(s_stream.good()){
                string substr;
                map[map.size() -1].push_back(s_stream.get() - 48);
            }
            map[map.size() -1].pop_back();
        }
    }

    bool validCoord(int x, int y){
        return x >= 0 && x < map.size() && y >= 0 && y < map[0].size();
    }


    void solvePart1(){
        bestScores = vector<vector<int>>(10, vector<int>(10, 0));
        bestScores[0][1] = 4;
    }

    Solution() {
        parseInput();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();

}