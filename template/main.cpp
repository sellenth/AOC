#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#if 1
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for(int i = a; a < b; a++)

typedef long long i64;

class Solution {

public:
    vector<vector<int>> map;

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
        }
    }

    void solvePart1(){
        cout << map[1][2] << endl;
    }

    Solution() {
        parseInput();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();

}