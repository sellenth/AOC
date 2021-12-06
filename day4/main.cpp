#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

class Board{
    public:
    vector<vector<int>> board;

    Board(){
        board = {};
    }

    void addRow(vector<int> row){
        board.push_back(row);
    }

    void printBoard(){
        for (auto &r : board){
            for (auto &c : r){
                cout << c << ' ';
            }
            cout << endl;
        }
    }
};

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
void parseNumbers(string line, vector<int> &numbers, char delim){
    stringstream s_stream(line);
    while(s_stream.good()){
        string substr;
        getline(s_stream, substr, delim);
        substr = trim(substr);
        if (substr.length() == 0){
            continue;
        }
        numbers.push_back(stoi(substr));
    }
}

int part1()
{
    char filename[] = "./ex.txt";
    //char filename[] = "./input.txt";
    ifstream in(filename);
    vector<int> numbers;
    vector<Board> boards;

    string line;
    getline(in, line);
    parseNumbers(line, numbers, ',');

    int board_idx = 0;
    while(in.good()){
        getline(in, line);
        Board b = Board();
        boards.push_back(b);

        for (int i = 0; i < 5; i++){
            getline(in, line);
            vector<int> row;
            parseNumbers(line, row, ' ');
            boards[board_idx].addRow(row);

        }
        board_idx++;
    }

    boards[2].printBoard();
    return 0;
}

int main()
{
    part1();
}