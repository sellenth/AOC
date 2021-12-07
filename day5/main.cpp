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


const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

void parseInput(string line, vector<vector<int>> &numbers){
    stringstream s_stream(line);
    while(s_stream.good()){
        string substr;
        vector<int> coord;
        getline(s_stream, substr, ',');
        coord.push_back(stoi(substr));
        getline(s_stream, substr, ' ');
        coord.push_back(stoi(substr));
        getline(s_stream, substr, ' ');
        numbers.push_back(coord);
        coord.clear();
        getline(s_stream, substr, ',');
        coord.push_back(stoi(substr));
        getline(s_stream, substr);
        coord.push_back(stoi(substr));
        numbers.push_back(coord);
    }
}

void insertCoordInSpace(vector<int> coord, std::unordered_map<vector<int>, int, VectorHasher>& vent_space, int& num_hazards){
    if(vent_space.find(coord) != vent_space.end()){
        if (vent_space.at(coord) == 1){
            num_hazards++;
        }
        vent_space.at(coord) += 1;
    } else {
        vent_space.insert({coord, 1});
    }
}

void plotVents1(vector<vector<int>>& coords, std::unordered_map<vector<int>, int, VectorHasher>& vent_space, int& num_hazards){
    for (int i = 0; i < coords.size(); i+=2){
        int& x1 = coords[i][0];
        int& y1 = coords[i][1];
        int& x2 = coords[i+1][0];
        int& y2 = coords[i+1][1];

        if (x1 == x2 && y1 == y2){
            insertCoordInSpace(coords[i], vent_space, num_hazards);
        }
        else if (y1 == y2){
            for (int x = min(x1, x2); x < max(x1, x2) + 1; x++){
                insertCoordInSpace(vector<int>{x, y1}, vent_space, num_hazards);
            }
        }
        else if (x1 == x2){
            for (int y = min(y1, y2); y < max(y1, y2) + 1; y++){
                insertCoordInSpace(vector<int>{x1, y}, vent_space, num_hazards);
            }

        }
    }

}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    ifstream in(filename);
    vector<vector<int>> coords;
    unordered_map<vector<int>, int, VectorHasher> vent_space;
    int num_hazards = 0;

    string line;
    while (in.good()){
        getline(in, line);
        parseInput(line, coords);
    }

    plotVents1(coords, vent_space, num_hazards);

    cout << num_hazards << endl;


    return 0;
}

void plotVents2(vector<vector<int>>& coords, std::unordered_map<vector<int>, int, VectorHasher>& vent_space, int& num_hazards){
    for (int i = 0; i < coords.size(); i+=2){
        int& x1 = coords[i][0];
        int& y1 = coords[i][1];
        int& x2 = coords[i+1][0];
        int& y2 = coords[i+1][1];

        if (x1 == x2 && y1 == y2){
            insertCoordInSpace(coords[i], vent_space, num_hazards);
        }
        else if (y1 == y2){
            for (int x = min(x1, x2); x < max(x1, x2) + 1; x++){
                insertCoordInSpace(vector<int>{x, y1}, vent_space, num_hazards);
            }
        }
        else if (x1 == x2){
            for (int y = min(y1, y2); y < max(y1, y2) + 1; y++){
                insertCoordInSpace(vector<int>{x1, y}, vent_space, num_hazards);
            }
        }
        else {
            int inc = 0;
            int sum = 0;
            if (x1 == min(x1, x2)){
               if (y1 < y2){
                   inc = 1;
               } else {
                   inc = -1;
               }
            }
            else {
               if (y2 < y1){
                   inc = 1;
               } else {
                   inc = -1;
               }
            }
            for (int x = min(x1, x2); x < max(x1, x2) + 1; x++){
                int yCoord = x1 == min(x1, x2) ? y1 : y2;
                yCoord += sum;
                insertCoordInSpace(vector<int>{x, yCoord}, vent_space, num_hazards);
                sum += inc; 
            }
        }
    }

}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    ifstream in(filename);
    vector<vector<int>> coords;
    unordered_map<vector<int>, int, VectorHasher> vent_space;
    int num_hazards = 0;

    string line;
    while (in.good()){
        getline(in, line);
        parseInput(line, coords);
    }

    plotVents2(coords, vent_space, num_hazards);

    cout << num_hazards << endl;


    return 0;
}


int main()
{
    //part1();
    part2();
}