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

#define F(i, a, b) for(int i = a; a < b; a++)

typedef long long i64;

class Solution {

public:
    i64 minX, maxX, minY, maxY;
    i64 apex;

    void parseInput(){
        ifstream in(FILENAME);

        string line;
        while (in.good()){
            getline(in, line);

            stringstream s_stream(line);
            while(s_stream.good()){
                string substr;
                getline(s_stream, substr, '=');
                getline(s_stream, substr, '.');
                minX = stoi(substr);
                s_stream.get();
                getline(s_stream, substr, ',');
                maxX = stoi(substr);

                getline(s_stream, substr, '=');
                getline(s_stream, substr, '.');
                minY = stoi(substr);
                s_stream.get();
                getline(s_stream, substr, '.');
                maxY = stoi(substr);
            }
        }
    }

    i64 triangularSum(i64 n){
        return abs(n) * (abs(n) + 1) / 2;
    }

    void solvePart1(){
        apex = triangularSum(abs(minY) - 1);
        i64 y0 = abs(minY) - 1;
        cout << "Launching the probe with initial Vy = " << y0 << " results in an apex of: " << apex << "units." << endl;
    }

    bool landsInTrench(int vx, int vy){
        i64 px = 0;
        i64 py = 0;
        while (true){
            if (py < minY){
                return false;
            }
            if (py <= maxY && py >= minY && px <= maxX && px >= minX){
                return true;
            } else {
                py += vy;
                vy -= 1;

                px += vx;
                if (vx != 0){
                    vx -= 1;
                }
            }
        }

    }

    void solvePart2(){
        unordered_map<string, int> uniqueVelocities;

        for (int vx = 0; vx <= maxX; vx++){
            for (int vy = minY; vy <= abs(minY); vy++){
                if (landsInTrench(vx, vy)){
                    string validVelocity = to_string(vx) + "," + to_string(vy);
                    cout << validVelocity << endl;
                    uniqueVelocities.emplace(make_pair(validVelocity, 1));
                }
            }

        }

        cout << "Number of unique velocities: " << uniqueVelocities.size() << endl;
    }

    Solution() {
        //Assumptions are made that the trench is down and to the right
        //of 0,0. (+x, -y)
        parseInput();
        solvePart1();
        landsInTrench(23, -9);
        solvePart2();
    }
};

int main() {
    Solution* s = new Solution();

}