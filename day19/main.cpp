#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>

using namespace std;

#if 1
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for(int i = a; a < b; i++)

typedef long long i64;

struct Point {
    i64 x;
    i64 y;
    i64 z;
};

string pToStr(Point &p){
return "" + to_string(p.x) + "," + to_string(p.y) + "," + to_string(p.z);
}

Point vectAdd(Point v1, Point v2){
return Point{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Point vectSub(Point v1, Point v2){
return Point{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

class Scanner {
    public: 
    int num;
    vector<Point> points;
    vector<vector<Point>> diffVectors;
    Point translation;
    bool oriented;

    Scanner(int n){
        num = n;
        points = {};
        oriented = false;
    }

    void calcAllDiffVectors(){
        diffVectors = {};
        for (int i = 0; i < points.size(); i++){
            diffVectors.push_back(vector<Point>(points.size()));
            for (int j = 0; j < points.size(); j++){
                if (i == j){
                    diffVectors[i][j] = Point{0,0,0};
                } else {
                    diffVectors[i][j] = differenceVector(points[i], points[j]);
                }
            }
        }
    }

    i64 magnitude(Point p){
        return pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2);
    }

    Point differenceVector(Point p1, Point p2){
        if (p1.z > p2.z){
            return Point{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
        } else {
            return Point{p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
        }
    }

    void rotatePoints(double pitch, double roll, double yaw) {
        double cosa = cos(yaw);
        double sina = sin(yaw);

        double cosb = cos(pitch);
        double sinb = sin(pitch);

        double cosc = cos(roll);
        double sinc = sin(roll);

        double Axx = cosa*cosb;
        double Axy = cosa*sinb*sinc - sina*cosc;
        double Axz = cosa*sinb*cosc + sina*sinc;

        double Ayx = sina*cosb;
        double Ayy = sina*sinb*sinc + cosa*cosc;
        double Ayz = sina*sinb*cosc - cosa*sinc;

        double Azx = -sinb;
        double Azy = cosb*sinc;
        double Azz = cosb*cosc;

        for (int i = 0; i < points.size(); i++) {
            double px = points[i].x;
            double py = points[i].y;
            double pz = points[i].z;

            points[i].x = round(Axx*px + Axy*py + Axz*pz);
            points[i].y = round(Ayx*px + Ayy*py + Ayz*pz);
            points[i].z = round(Azx*px + Azy*py + Azz*pz);
        }
    }

    void translatePoints(){
        for (int i = 0; i < points.size(); i++){
            points[i] = vectAdd(points[i], translation);
        }
    }

};

struct diffVectMatch {
    pair<int, int> baseVidx;
    pair<int, int> testVidx;
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
                Point p;
                p.x = stod(l.substr(0,firstComma));
                p.y = stod(l.substr(firstComma + 1, secondComma));
                p.z = stod(l.substr(secondComma + 1));
                scanners.back().points.push_back(p);
            }
        }

        scanners[0].oriented = true;
        scanners[0].translation = {0, 0, 0};
    }

    double magnitude(Point v){
        return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)); 
    }

    pair<int, int> findMatch(Point diffVector, Scanner &s){
        for (int i = 0; i < s.diffVectors.size(); i++){
            for (int j = 0; j < s.diffVectors[0].size(); j++){
                if (magnitude(diffVector) == magnitude(s.diffVectors[i][j])){
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1);
    }

    bool vectorMatch(Point &v1, Point &v2){
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }

    void printMatchList(Scanner &s1, Scanner &s2, vector<diffVectMatch> &matches){
        for (auto &match : matches){
            Point v1 = s1.diffVectors[match.baseVidx.first][match.baseVidx.second];
            Point v2 = s2.diffVectors[match.testVidx.first][match.testVidx.second];
            if (vectorMatch(v1, v2)){
                cout << "Match" << endl;
            } else {
                cout << v1.x << " " << v1.y << " " << v1.z << endl;
                cout << v2.x << " " << v2.y << " " << v2.z << endl << endl;
            }
        }
    }

    bool allMatch(Scanner &s1, Scanner &s2, vector<diffVectMatch> &matches){
        for (auto &match : matches){
            Point v1 = s1.diffVectors[match.baseVidx.first][match.baseVidx.second];
            Point v2 = s2.diffVectors[match.testVidx.first][match.testVidx.second];
            if (!vectorMatch(v1, v2)){
                return false;
            }
        }
        return true;
    }

    vector<diffVectMatch> getMatchList(Scanner &s1, Scanner &s2){
        vector<diffVectMatch> matchList;
        for (int i = 0; i < s1.diffVectors.size(); i++){
            for (int j = i+1; j < s1.diffVectors[0].size(); j++){
                pair<int, int> res = findMatch(s1.diffVectors[i][j], s2);
                if (res.first != -1 && res.second != -1){
                    diffVectMatch match = {make_pair(i,j), res};
                    matchList.push_back(match);
                    break;
                }
            }
        }
        return matchList;
    }


    bool orientScanner(Scanner &s1, Scanner &s2, vector<diffVectMatch> &matches){
        /*
        for (int x = 0; x < 4; x++){
            for (int y = 0; y < 3; y++){
                for (int z = 0; z < 2; z++){
                    s2.rotatePoints(1.571, 0, 0);
                    s2.calcAllDiffVectors();
                    if (allMatch(s1, s2, matches)){
                        //printMatchList(s1, s2, matches);
                        //cout << s1.points[matches[0].baseVidx.first].x << s1.points[matches[0].baseVidx.first].y << s1.points[matches[0].baseVidx.first].z << endl;
                        return true;
                    }
                }
            }
        }
    
        return false;
        */

        for (int x = 0; x < 4; x++){
            s2.rotatePoints(1.571, 0, 0);
            s2.calcAllDiffVectors();
            if (allMatch(s1, s2, matches)){
                return true;
            }
        }

        s2.rotatePoints(0, 3.1415, 0);

        for (int x = 0; x < 4; x++){
            s2.rotatePoints(1.571, 0, 0);
            s2.calcAllDiffVectors();
            if (allMatch(s1, s2, matches)){
                return true;
            }
        }

        s2.rotatePoints(0, 1.571, 0);

        for (int z = 0; z < 4; z++){
            s2.rotatePoints(0, 0, 1.571);
            s2.calcAllDiffVectors();
            if (allMatch(s1, s2, matches)){
                return true;
            }
        }

        s2.rotatePoints(3.1415, 0, 0);

        for (int z = 0; z < 4; z++){
            s2.rotatePoints(0, 0, 1.571);
            s2.calcAllDiffVectors();
            if (allMatch(s1, s2, matches)){
                return true;
            }
        }

        s2.rotatePoints(1.571, 0, 0);

        for (int y = 0; y < 4; y++){
            s2.rotatePoints(0, 1.571, 0);
            s2.calcAllDiffVectors();
            if (allMatch(s1, s2, matches)){
                return true;
            }
        }

        s2.rotatePoints(3.1415, 0, 0);

        for (int y = 0; y < 4; y++){
            s2.rotatePoints(0, 1.571, 0);
            s2.calcAllDiffVectors();
            if (allMatch(s1, s2, matches)){
                return true;
            }

        }
        return false;

    }



    void solveTranslation(Scanner &s1, vector<int> &s1u, Scanner &s2, vector<int> &s2u){
        Point init = {-1, -1, -1};
        Point highestP1 = {-1, -1, -1};
        Point highestP2 = {-1, -1, -1};

        for (auto &idx : s1u){
            if (s1.points[idx].z > highestP1.z || vectorMatch(highestP1, init)){
                highestP1 = s1.points[idx];
            }
        } 

        for (auto &idx : s2u){
            if (s2.points[idx].z > highestP2.z || vectorMatch(highestP2, init)){
                highestP2 = s2.points[idx];
            }
        } 

        cout << "Highest point in scanner " << s1.num << " is " << pToStr(highestP1) << endl;
        cout << "Highest point in scanner " << s2.num << " is " << pToStr(highestP2) << endl;

        Point translation = vectSub(highestP1, highestP2);
        cout << "Translating scanner " << s2.num << " by " << pToStr(translation) << endl;
        s2.translation = translation;
        s2.translatePoints();
    }

    vector<int> findUniqueIndices(int which, vector<diffVectMatch> &matches){
        vector<int> uniques = {};
        unordered_map<int, int> res = {};
        for (int i = 0; i < matches.size(); i++){
            if (which == 0){
                res.emplace(matches[i].baseVidx.first, 1);
                res.emplace(matches[i].baseVidx.second, 1);
            } else {
                res.emplace(matches[i].testVidx.first, 1);
                res.emplace(matches[i].testVidx.second, 1);
            }
        }

        for (auto &keyValue : res){
            uniques.push_back(keyValue.first);
        }

        return uniques;
    }

    void countAllUniquePoints(){
        unordered_map<string, int> uniques;
        for (auto &s : scanners){
            for (auto &p : s.points){
                uniques.emplace(pToStr(p), 1);
            }
        }

        cout << uniques.size() << endl;
    }

    void solvePart1(){
        for (auto &s : scanners){
            s.calcAllDiffVectors();
        }

        //vector<diffVectMatch> matches = getMatchList(scanners[1], scanners[2]);

        for (int i = 0; i < scanners.size(); i++){
            for (int j = 0; j < scanners.size(); j++){
                if (scanners[i].oriented && !scanners[j].oriented){
                    vector<diffVectMatch> matches = getMatchList(scanners[i], scanners[j]);
                    if (matches.size() >= 11){
                        if (orientScanner(scanners[i], scanners[j], matches)){
                            scanners[j].oriented = true;
                            vector<int> s1UniqueIndices = findUniqueIndices(0, matches);
                            vector<int> s2UniqueIndices = findUniqueIndices(1, matches);
                            cout << "Scanner " << j << " has been oriented to scanner " << i << endl;

                            solveTranslation(scanners[i], s1UniqueIndices, scanners[j], s2UniqueIndices); 
                        } else {
                            cout << "Scanner " << j << " couldn't be oriented to scanner " << i << endl; 
                        }
                    }
                }
            }
        }

        countAllUniquePoints();


    }

    Solution() {
        parseInput();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();

}