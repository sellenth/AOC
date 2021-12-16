#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#if 1
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

    void printInOrder(){
        for (int i = 0; i < map.size(); i++){
            int x = 0;
            for (int y = i; y >= 0; y--){
                cout << map[x][y];
                x++;
            }
            cout << endl;
        }
    }

    void calcBestScores(){
        for (int i = 1; i < map.size(); i++){
            int x = 0;
            for (int y = i; y >= 0; y--){
                if (x == 0){
                    bestScores[x][y] = bestScores[x][y-1] + map[x][y];
                } else if (y == 0){
                    bestScores[x][y] = bestScores[x-1][y] + map[x][y];
                }
                else {
                    bestScores[x][y] = min(bestScores[x-1][y], bestScores[x][y-1]) + map[x][y];
                }
                x++;
            }
        }

        for (int i = 1; i < map.size(); i++){
            int y = map.size() - 1;
            for (int x = i; x < map.size(); x++){
                bestScores[x][y] = min(bestScores[x-1][y], bestScores[x][y-1]) + map[x][y];
                y--;
            }
        }

    }

    bool validCoord(int x, int y){
        return x >= 0 && x < map.size() && y >= 0 && y < map[0].size();
    }

    void printBestScores(){
        for (int i = 0; i < bestScores.size(); i++){
            for (int j = 0; j < bestScores[0].size(); j++){
                cout << bestScores[i][j] << ' ';
            }
            cout << endl;
        }
    }


    void solvePart1(){
        bestScores = vector<vector<int>>(map.size(), vector<int>(map[0].size(), 9));
        bestScores[0][0] = 0;

        calcBestScores();

        printBestScores();
    }

    Solution() {
        parseInput();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();

}