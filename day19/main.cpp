#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

#define TESTING 0

#if TESTING
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for(int i = a; a < b; i++)


typedef long long i64;

class Point {
    public:
    i64 x, y, z;
    Point(){
        x = 0;
        y = 0;
        z = 0;
    }

    Point(i64 a, i64 b, i64 c){
        x = a;
        y = b;
        z = c;
    }

    Point operator+(const Point& p2){
        return Point(x + p2.x, y + p2.y, z + p2.z);
    }

    Point operator-(const Point& p2){
        return Point(x - p2.x, y - p2.y, z - p2.z);
    }

    bool operator==(const Point& p2){
        return x == p2.x && y == p2.y && z == p2.z;
    }

    friend ostream& operator<<(ostream &os, const Point& p);

    string toString() const{
        return to_string(x) + "," + to_string(y) + "," + to_string(z);
    }

    i64 magnitude(){
        return pow(x, 2) + pow(y, 2) + pow(z, 2);
    }
};

ostream& operator<<(ostream &os, const Point& p){
    os << p.toString();
    return os;
}

typedef Point vec3;
vector<vec3> OFFSETS = {vec3(0, 0, 0)};

class Scanner {
    public: 
    int num;
    vector<Point> points;
    vector<vector<vec3>> diffVectors;
    bool oriented;
    bool merged;

    Scanner(int n){
        num = n;
        points = {};
        diffVectors = {};
        oriented = false;
        merged = false;
    }

    void calcAllDiffVectors(){
        diffVectors = {};
        for (int i = 0; i < points.size(); i++){
            diffVectors.push_back(vector<vec3>(points.size()));
            for (int j = 0; j < points.size(); j++){
                diffVectors[i][j] = points[i] - points[j];
            }
        }
    }

    void translatePoints(vec3 translation){
        for (int i = 0; i < points.size(); i++){
            points[i] = points[i] + translation;
        }
    }
};

class Solution {

public:
    vector<Scanner> scanners;

    void parseInput(){
        ifstream in(FILENAME);
        scanners = {};
        int i = 0;

        vector<string> lines;
        string line;
        while (in.good()){
            getline(in, line);
            lines.push_back(line);
        }


        for (auto &l : lines){
            if (l.empty()){
                continue;
            }
            if (l[1] == '-'){
                Scanner s(i);
                scanners.push_back(s);
                i++;
            } else {
                int firstComma = l.find(',');
                int secondComma = l.find(',', firstComma + 1);
                Point p(0, 0, 0);
                p.x = stoi(l.substr(0,firstComma));
                p.y = stoi(l.substr(firstComma + 1, secondComma));
                p.z = stoi(l.substr(secondComma + 1));
                scanners.back().points.push_back(p);
            }
        }
    }

    Point getOrientation(Point &p, int i){
        Point new_point(0, 0, 0);

        switch (i / 4){
            case 0: {
                // Unchanged
                new_point = Point(p.x, p.y, p.z);
                break;
            }
            case 1: {
                // Rotate 180 degrees around the y-axis so z points towards -z
                new_point = Point(-1 * p.x, p.y, -1 * p.z);
                break;
            }
            case 2: {
                // Rotate 90 degrees around the y-axis so that z points towards -x
                new_point = Point(p.z, p.y, -1 * p.x);
                break;
            }
            case 3: {
                // Rotate 90 degrees around the y-axis so that z points towards +x
                new_point = Point(-1 * p.z, p.y, p.x);
                break;
            }
            case 4: {
                // Rotate 90 degrees around the x-axis so that z points towards -y
                new_point = Point(p.x, p.z, -1 * p.y);
                break;
            }
            case 5: {
                // Rotate 90 degrees around the x-axis so that z points towards +y
                new_point = Point(p.x, -1 * p.z, p.y);
                break;
            }
            default: assert(0);
        }

        switch (i % 4){
            case 0: {break;}
            case 1: {new_point = Point(-1 * new_point.y, new_point.x, new_point.z);} break;
            case 2: {new_point = Point(-1 * new_point.x, -1 * new_point.y, new_point.z);} break;
            case 3: {new_point = Point(new_point.y, -1 * new_point.x, new_point.z);} break;
            default: assert(0);
        }

        return new_point;
    }

    bool twelveMatch(Scanner &s1, Scanner &s2, vec3 &translation){
        int numMatch = 0;
        for (int i = 0; i < s2.diffVectors.size(); i++){
            for (int j = 0; j < s2.diffVectors[0].size(); j++){
                if (i == j){
                    continue;
                }
                for (int k = 0; k < s1.diffVectors.size(); k++){
                    for (int m = 0; m < s1.diffVectors[0].size(); m++){
                        if (k == m){
                            continue;
                        }
                        if (s2.diffVectors[i][j] == s1.diffVectors[k][m]){
                            numMatch++;
                            if (numMatch >= 12){
                                translation = s1.points[k] - s2.points[i];
                                OFFSETS.push_back(translation);
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    bool orientScanner(Scanner &s1, Scanner &s2, vec3 &translation){
        vector<Point> orig_points = s2.points;

        for (int i = 0; i < 24; i++){
            for (auto &p : s2.points){
                p = getOrientation(p, i);
            }
        
            s2.calcAllDiffVectors();
            if(twelveMatch(s1, s2, translation)){
                return true;
            }
            s2.points = orig_points;
        }
        return false;
    }

    void checkScannerPairs(){
        for (int i = 0; i < scanners.size(); i++){
            for (int j = i+1; j < scanners.size(); j++){
                vec3 translation;
                if (orientScanner(scanners[i], scanners[j], translation)){
                    cout << "Scanner " << scanners[j].num << " has been oriented to scanner " << scanners[i].num << endl;
                    scanners[j].translatePoints(translation);
                    mergeScanner(scanners[i], scanners[j]);
                    scanners.erase(scanners.begin() + j);
                    return;
                }
            }
        }
    }

    void mergeScanner(Scanner &s1, Scanner &s2){
        unordered_map<string, int> coordsUsed = {};
        for (auto &p : s1.points){
            coordsUsed.emplace(p.toString(), 1);
        }
        for (auto &p : s2.points){
            if (coordsUsed.count(p.toString()) == 0){
                coordsUsed.emplace(p.toString(), 1);
                s1.points.push_back(p);
            }
        }
        s1.calcAllDiffVectors();
    }

    void solvePart1(){
        for (auto &s : scanners){
            s.calcAllDiffVectors();
        }

        while (scanners.size() > 1){
            checkScannerPairs();
           cout << scanners[0].points.size() << endl;
        }

        cout << scanners[0].points.size() << endl;

    }

    void testPart1(){
        unordered_map<string, int> verify24 = {};
        Point orig_point = scanners[0].points[0];
        assert(orig_point == Point(-880, -557, 778));
        for (int i = 0; i < 24; i++){
            verify24.emplace(getOrientation(orig_point, i).toString(), 1);
        }
        verify24.emplace(getOrientation(orig_point, 0).toString(), 1);
        assert(verify24.size() == 24);

        assert(!(orig_point == Point()));
        assert(orig_point - Point(1, 1, 1) == Point(-881, -558, 777));
        scanners[0].translatePoints(vec3(1, 1, 1));
        assert(orig_point + Point(1, 1, 1) == scanners[0].points[0]);
        scanners[0].translatePoints(vec3(-1, -1, -1));
        assert(scanners[0].points[0] == orig_point);

        return;
    }

    i64 manhattanDistance(vec3 &v1, vec3 &v2){
        return abs(v1.x - v2.x) + abs(v1.y - v2.y) + abs(v1.z - v2.z);
    }

    void solvePart2(){
        i64 largest = 0;
        for (int i = 0; i < OFFSETS.size(); i++){
            for (int j = i+1; j < OFFSETS.size(); j++){
                i64 d = manhattanDistance(OFFSETS[i], OFFSETS[j]);
                if (d > largest){
                    largest = d;
                }
            }
        }

        cout << "Part2 answer: " << largest;
    }

    Solution() {
        parseInput();
        //testPart1();
        solvePart1();
        solvePart2();
    }
};

int main() {
    Solution* s = new Solution();
    return 1;
}