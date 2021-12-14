#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

void parseInput(string line, unordered_map<string, pair<int,int>> &input){
    stringstream s_stream(line);
    int xAsInt, yAsInt;
    while(s_stream.good()){
        string x, y;
        getline(s_stream, x, ',');
        getline(s_stream, y);

        xAsInt = stoi(x);
        yAsInt = stoi(y);

        input.emplace(line, make_pair(xAsInt, yAsInt));
    }
}

void parseFolds(string line, vector<pair<char, int>> &input){
    stringstream s_stream(line);
    while(s_stream.good()){
        string x, y;
        getline(s_stream, x, '=');
        getline(s_stream, y);
        input.push_back(make_pair(x[x.size() - 1], stoi(y)));
    }
}

string makeStringFromInts(int x, int y){
    return to_string(x) + ',' + to_string(y);
}

void dumpPaper(unordered_map<string, pair<int, int>> &paper){
    int maxX = 0;
    int maxY = 0;
    for (auto &it : paper){
        auto &pair = it.second;
        if (pair.first > maxX){
            maxX = pair.first;
        }
        if (pair.second > maxY){
            maxY = pair.second;
        }
    }

    for (int y = 0; y <= maxY; y++){
        for (int x = 0; x <= maxX; x++){
            if (paper.find(makeStringFromInts(x, y)) != paper.end()) {
                cout << '#';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void mergeLines(vector<char> &lineKeep, vector<char> &lineErase){
    for (int i = 0; i < lineKeep.size(); i++){
        if (lineErase[i] == '#'){
            lineKeep[i] = '#';
        }
    }
}

void foldLeft(unordered_map<string, pair<int, int>> &paper, pair<char, int> &fold){
    unordered_map<string, pair<int, int>> newPaper;
    for (auto &it : paper){
        auto &pair = it.second;
        if (pair.first > fold.second){
            int newX = fold.second - (pair.first - fold.second);
            newPaper.emplace(makeStringFromInts(newX, pair.second), make_pair(newX, pair.second));
        } else {
            newPaper.emplace(it.first, it.second);
        }
    }

    paper = newPaper;

}

void foldUp(unordered_map<string, pair<int, int>> &paper, pair<char, int> &fold){
    unordered_map<string, pair<int, int>> newPaper;
    for (auto &it : paper){
        auto &pair = it.second;
        if (pair.second > fold.second){
            int newY = fold.second - (pair.second - fold.second);
            newPaper.emplace(makeStringFromInts(pair.first, newY), make_pair(pair.first, newY));
        } else {
            newPaper.emplace(it.first, it.second);
        }
    }

    paper = newPaper;
}

int part1()
{
    char filename[] = "./ex.txt";
    //char filename[] = "./input.txt";

    ifstream in(filename);
    int maxX = 0;
    int maxY = 0;
    unordered_map<string, pair<int,int>> paper;
    vector<pair<char, int>> folds;

    {
    string line;
    while (in.good()){
        getline(in, line);
        if (line.empty()){
            break;
        }
        parseInput(line, paper);
    }

    while (in.good()){
        getline(in, line);
        parseFolds(line, folds);
    }
    in.close();
    }


    for (int i = 0; i < 1; i++){
        if (folds[i].first == 'x'){
            foldLeft(paper, folds[i]);
        } else {
            foldUp(paper, folds[i]);
        }
    }

    dumpPaper(paper);

    cout << "Number of dots: " << paper.size() << endl;

    return 0;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    int maxX = 0;
    int maxY = 0;
    unordered_map<string, pair<int,int>> paper;
    vector<pair<char, int>> folds;

    {
    string line;
    while (in.good()){
        getline(in, line);
        if (line.empty()){
            break;
        }
        parseInput(line, paper);
    }

    while (in.good()){
        getline(in, line);
        parseFolds(line, folds);
    }
    in.close();
    }

    //dumpPaper(paper);
    cout << endl;

    for (int i = 0; i < folds.size(); i++){
        if (folds[i].first == 'x'){
            foldLeft(paper, folds[i]);
        } else {
            foldUp(paper, folds[i]);
        }
    }

    dumpPaper(paper);

    return 0;
}


int main()
{
    //part1();
    part2();
}