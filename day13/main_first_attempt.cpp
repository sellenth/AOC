#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void parseInput(string line, vector<pair<int,int>> &input, int &maxX, int &maxY){
    stringstream s_stream(line);
    int xAsInt, yAsInt;
    while(s_stream.good()){
        string x, y;
        getline(s_stream, x, ',');
        getline(s_stream, y);

        xAsInt = stoi(x);
        yAsInt = stoi(y);

        if (xAsInt > maxX){
            maxX = xAsInt;
        }
        if (yAsInt > maxY){
            maxY = yAsInt;
        }
        input.push_back(make_pair(xAsInt, yAsInt));
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

void writePaper(vector<pair<int,int>> &data, vector<vector<char>> &paper, int &maxX, int &maxY){
    for (int i = 0; i < maxY + 1; i++){
        paper.push_back(vector<char>(maxX + 1, '.'));
    } 

    for (auto &point : data){
        paper[point.second][point.first] = '#';
    }
}

void dumpPaper(vector<vector<char>> &paper){
    int maxX = 0;
    int maxY = 0;
    for (auto &pair : paper){
        if (paper.first > maxX){
            maxX = paper.first;
        }
        if (paper.second > maxY){
            maxY = paper.second;
        }
    }

    for (int i = 0; i < maxY; i++){
        for (int j = 0; j < maxX; j++){
            if (find())
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

void foldLeft(vector<vector<char>> &paper, pair<char, int> &fold){
    for (int i = 0; i < paper.size(); i++){
        for (int c = paper[i].size() - 2 * fold.second - 1; c < paper[i].size() - fold.second - 1; c++){
            if(paper[i][paper[i].size() - 1 - c] == '#') paper[i][c] = '#';
        }
        for (int j = 0; j <= fold.second; j++){
            paper[i].pop_back();
        }
    }
}

void foldUp(vector<vector<char>> &paper, pair<char, int> &fold){
    //The line that we are folding onto is the size of the sheet 
    //minus twice the fold size and then minus one for the line
    //that the fold itself is on
    //(this involved some trial and error)
    int destinationLine = fold.second - (paper.size() - 1 - fold.second);
    for (int i = paper.size() - 1; i > fold.second; i--){
        mergeLines(paper[destinationLine], paper[i]);
        destinationLine++;
    }
    for (int lineCount = paper.size(); lineCount >= fold.second; lineCount--){
        paper.pop_back();
    }
}

int countDots(vector<vector<char>> &paper){
    int sum = 0;
    for (int i = 0; i < paper.size(); i++){
        for (int j = 0; j < paper[0].size(); j++){
            if (paper[i][j] == '#'){
                sum++;
            }
        }
    }
    return sum;
}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    int maxX = 0;
    int maxY = 0;
    vector<pair<int, int>> in_data;
    vector<vector<char>> paper;
    vector<pair<char, int>> folds;

    {
    string line;
    while (in.good()){
        getline(in, line);
        if (line.empty()){
            break;
        }
        parseInput(line, in_data, maxX, maxY);
    }

    while (in.good()){
        getline(in, line);
        parseFolds(line, folds);
    }
    in.close();
    }

    writePaper(in_data, paper, maxX, maxY);
    //dumpPaper(paper);
    cout << endl;

    for (int i = 0; i < 1; i++){
        if (folds[i].first == 'x'){
            foldLeft(paper, folds[i]);
        } else {
            foldUp(paper, folds[i]);
        }
    }

    dumpPaper(paper);

    cout << countDots(paper);

    return 0;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    int maxX = 0;
    int maxY = 0;
    vector<pair<int, int>> in_data;
    vector<vector<char>> paper;
    vector<pair<char, int>> folds;

    {
    string line;
    while (in.good()){
        getline(in, line);
        if (line.empty()){
            break;
        }
        parseInput(line, in_data, maxX, maxY);
    }

    while (in.good()){
        getline(in, line);
        parseFolds(line, folds);
    }
    in.close();
    }

    writePaper(in_data, paper, maxX, maxY);
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

    cout << countDots(paper);

    return 0;
}


int main()
{
    //part1();
    part2();
}