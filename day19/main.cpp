#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include "./glm/glm.hpp"
#include "./glm/gtx/rotate_vector.hpp"
#include "./glm/gtc/constants.hpp"
#include "./glm/gtc/epsilon.hpp"

using namespace std;
using glm::vec3;

#if 0
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for(int i = a; a < b; i++)

typedef long long i64;

enum COMPONENT {X = 1, Y = 2, Z = 3};

int orientations[24][3] = {{1, 2, 3},
    {2, 1, 3},
    {-2, 1, 3},
    {1, -2, 3},

    {1, 2, -3},
    {2, 1, -3},
    {-2, 1, -3},
    {1, -2, -3},

    {1, 3, 2},
    {3, 1, 2},
    {-3, 1, 2},
    {1, -3, 2},

    {1, 3, -2},
    {3, 1, -2},
    {-3, 1, -2},
    {1, -3, -2},

    {3, 2, 1},
    {2, 3, 1},
    {-2, 3, 1},
    {3, -2, 1},

    {3, 2, -1},
    {2, 3, -1},
    {-2, 3, -1},
    {3, -2, -1}};      

string pToStr(vec3 v){
    return to_string(int(v.x)) + "," + to_string(int(v.y)) + "," + to_string(int(v.z));
}

class Scanner {
    public: 
    int num;
    vector<vec3> points;
    vector<vector<vec3>> diffVectors;
    vec3 translation;
    bool oriented;
    int translatedTo;

    Scanner(int n){
        num = n;
        points = {};
        diffVectors = {};
        translation = {0, 0, 0};
        oriented = false;
        translatedTo = n;
    }

    void calcAllDiffVectors(){
        diffVectors = {};
        for (int i = 0; i < points.size(); i++){
            diffVectors.push_back(vector<vec3>(points.size()));
            for (int j = 0; j < points.size(); j++){
                diffVectors[i][j] = differenceVector(points[i], points[j]);
            }
        }
    }

    vec3 differenceVector(vec3 p1, vec3 p2){
        if (p1.z > p2.z){
            return p1 - p2;
        } else {
            return p2 - p1;
        }
    }

    void rotatePointsX(){
        for (auto &p : points){
            p = glm::vec3(p.x, p.z, -1 * p.y);
        }
    }

    void rotatePointsY(){
        for (auto &p : points){
            p = glm::vec3(p.z, p.y, -1 * p.x);
        }
    }

    void rotatePointsZ(){
        for (auto &p : points){
            p = glm::vec3(p.y, -1 * p.x, p.z);
        }
    }

    void translatePoints(){
        for (int i = 0; i < points.size(); i++){
            points[i] = points[i] + translation;
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
                vec3 p;
                p.x = stoi(l.substr(0,firstComma));
                p.y = stoi(l.substr(firstComma + 1, secondComma));
                p.z = stoi(l.substr(secondComma + 1));
                scanners.back().points.push_back(p);
            }
        }

        scanners[0].oriented = true;
    }


    void printMatchList(Scanner &s1, Scanner &s2, vector<diffVectMatch> &matches){
        for (auto &match : matches){
            vec3 v1 = s1.diffVectors[match.baseVidx.first][match.baseVidx.second];
            vec3 v2 = s2.diffVectors[match.testVidx.first][match.testVidx.second];
            if (glm::all(glm::epsilonEqual(v1, v2, FLT_EPSILON))){
                cout << "Match" << endl;
            } else {
                cout << v1.x << " " << v1.y << " " << v1.z << endl;
                cout << v2.x << " " << v2.y << " " << v2.z << endl << endl;
            }
        }
    }

    bool allMatch(Scanner &s1, Scanner &s2, vector<diffVectMatch> &matches){
        for (auto &match : matches){
            vec3 v1 = s1.diffVectors[match.baseVidx.first][match.baseVidx.second];
            vec3 v2 = s2.diffVectors[match.testVidx.first][match.testVidx.second];
            if (!glm::all(glm::epsilonEqual(v1, v2, FLT_EPSILON))){
                return false;
            }
        }
        return true;
    }

    pair<int, int> findMatch(vec3 &diffVector, Scanner &s){
        for (int i = 0; i < s.diffVectors.size(); i++){
            for (int j = 0; j < s.diffVectors[0].size(); j++){
                if (glm::epsilonEqual(glm::length(diffVector), glm::length(s.diffVectors[i][j]), FLT_EPSILON)){
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1);
    }

    vector<diffVectMatch> getMatchList(Scanner &s1, Scanner &s2){
        vector<diffVectMatch> matchList;
        for (int i = 0; i < s1.diffVectors.size(); i++){
            for (int j = i+1; j < s1.diffVectors[i].size(); j++){
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

/*
    float getCoorespondingComponent(int orientationIdx, COMPONENT c, vec3 &point){
        switch(orientations[orientationIdx][c]){
            case -1:
                return point.x * -1.f;
            case -2:
                return point.y * -1.f;
            case -3:
                return point.z * -1.f;
            case 1:
                return point.x;
            case 2:
                return point.y;
            case 3:
                return point.z;
            default:
                return 0.f;
        }
    }
    */

    float getCoorespondingComponent(int v, vec3 &point){
        switch(v){
            case -1:
                return point.x * -1.f;
            case -2:
                return point.y * -1.f;
            case -3:
                return point.z * -1.f;
            case 1:
                return point.x;
            case 2:
                return point.y;
            case 3:
                return point.z;
            default:
                return 0.f;
        }
    }

    bool orientScanner(Scanner &s1, Scanner &s2, vector<diffVectMatch> &matches){
        vector<vec3> orig_points = s2.points;
        /*

        [x, y, z]
        [y, x, z]
        [-y, x, z]
        [x, -y, z]
        
        [x, y, -z]
        [y, x, -z]
        [-y, x, -z]
        [x, -y, -z]
        
        [x, z, y]
        [z, x, y]
        [-z, x, y]
        [x, -z, y]
        
        [x, z, -y]
        [z, x, -y]
        [-z, x, -y]
        [x, -z, -y]

        [z, y, x]
        [y, z, x]
        [-y, z, x]
        [z, -y, x]
        
        [z, y, -x]
        [y, z, -x]
        [-y, z, -x]
        [z, -y, -x]


        for (int i = 0; i < 24; i++){
            for (auto &p : s2.points){
                vec3 newPoint(
                    getCoorespondingComponent(i, X, p),
                    getCoorespondingComponent(i, Y, p),
                    getCoorespondingComponent(i, Z, p));
                p = newPoint;
            }
        */
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 4; j++){
                for (int k = 0; k < 2; k++){
                    vector<int> possibles;
                    int xComp, yComp, zComp;
                    switch(i){
                        case 0: case 1:
                            xComp = i % 2 ? 1 : -1;
                            possibles = {2, 3};
                            break;
                        case 2: case 3:
                            xComp = i % 2 ? 2 : -2;
                            possibles = {3, 1};
                            break;
                        case 4: case 5:
                            xComp = i % 2 ? 3 : -3;
                            possibles = {1, 2};
                            break;
                        default:
                            break;
                    }

                    switch(j){
                        case 0: case 1:
                        {
                            int val = possibles[0];
                            possibles.erase(possibles.begin());
                            yComp = j == 0 ? val * -1 : val;
                        }
                            break;
                        case 2: case 3:
                        {
                            int val = possibles[1];
                            possibles.erase(possibles.begin()+1);
                            yComp = j == 2 ? val * -1 : val;
                        }
                            break;
                        default:
                            break;
                    }

                    zComp = k == 0 ? possibles[0] * -1 : possibles[0];

                    for (auto &p : s2.points){
                        vec3 newPoint(
                            getCoorespondingComponent(xComp, p),
                            getCoorespondingComponent(yComp, p),
                            getCoorespondingComponent(zComp, p));
                        p = newPoint;
                    }

                    s2.calcAllDiffVectors();
                    if(allMatch(s1, s2, matches)){
                        return true;
                    }
                    s2.points = orig_points;

                }
            }
        }



        return false;
    }

    void solveTranslation(Scanner &s1, vector<int> &s1u, Scanner &s2, vector<int> &s2u){
        vec3 init = {-1, -1, -1};
        vec3 highestP1 = {-1, -1, -1};
        vec3 highestP2 = {-1, -1, -1};

        for (auto &idx : s1u){
            if (s1.points[idx].z > highestP1.z || highestP1 == init){
                highestP1 = s1.points[idx];
            }
        } 

        for (auto &idx : s2u){
            if (s2.points[idx].z > highestP2.z || highestP2 == init){
                highestP2 = s2.points[idx];
            }
        } 

        cout << "Highest point in scanner " << s1.num << " is " << pToStr(highestP1) << endl;
        cout << "Highest point in scanner " << s2.num << " is " << pToStr(highestP2) << endl;

        vec3 translation = highestP1 - highestP2;
        cout << "Translating scanner " << s2.num << " by " << pToStr(translation) << endl;
        s2.translation = translation;
        s2.translatePoints();
        s2.translatedTo = s1.translatedTo;

        for (int i = 0; i < s2.points.size(); i++){
            if (find(s2u.begin(), s2u.end(), i) == s2u.end()){
                s1.points.push_back(s2.points[i]);
            }
        }
        s1.calcAllDiffVectors();
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

        Scanner& sZero = scanners[0];

        while (scanners.size() > 1){
            for (int i = 1; i < scanners.size(); i++){
                vector<diffVectMatch> matches = getMatchList(sZero, scanners[i]);
                //printMatchList(sZero, scanners[i], matches);
                if (matches.size() >= 5){
                    if (orientScanner(sZero, scanners[i], matches)){
                        scanners[i].oriented = true;
                        vector<int> s1UniqueIndices = findUniqueIndices(0, matches);
                        vector<int> s2UniqueIndices = findUniqueIndices(1, matches);
                        cout << "Scanner " << scanners[i].num << " has been oriented to scanner " << sZero.num << endl;

                        solveTranslation(sZero, s1UniqueIndices, scanners[i], s2UniqueIndices); 
                        scanners.erase(scanners.begin() + i);
                        break;
                    } else {
                        cout << "Scanner " << scanners[i].num << " couldn't be oriented to " << sZero.num << endl;
                    }
                } else {
                    cout << "Scanner " << scanners[i].num << " only has " << matches.size() << " matches." << endl;
                }
            }
        }


        cout << scanners[0].points.size() << endl;
        countAllUniquePoints();


    }

    Solution() {
        parseInput();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();
    return 1;
}