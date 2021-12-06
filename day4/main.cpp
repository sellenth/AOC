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
    int board_idx;

    Board(){
        board = {};
    }

    Board(int idx){
        board = {};
        board_idx = idx;
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

    int calculateScore(int call){
        int accum = 0;
        for (auto &r : board){
            for (auto &c : r){
                if (c != -1){
                    accum += c;
                }
            }
        }
        return accum * call;
    }

    void markBoard(int call){
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                if (board[i][j] == call){
                    board[i][j] = -1;
                    return;
                }
            }
        }
    }

    bool checkIfWon(){
        for(int i = 0; i < board.size(); i++){
            if (board[i][0] == -1){
                int accum = 0;
                for(int j = 0; j < board[i].size(); j++){
                    if (board[i][j] == -1){
                        accum++;
                    }
                }
                if (accum == board[i].size()){
                    return true;
                }
            }
        }

        for(int i = 0; i < board[i].size(); i++){
            if (board[0][i] == -1){
                int accum = 0;
                for(int j = 0; j < board.size(); j++){
                    if (board[j][i] == -1){
                        accum++;
                    }
                }
                if (accum == board.size()){
                    return true;
                }
            }
        }
        return false;
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
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
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

    for (auto &call : numbers){
        for (int i = 0; i < boards.size(); i++){
            boards[i].markBoard(call);
            if (boards[i].checkIfWon()){
                cout << "Winning board is: " << i << endl;
                cout << "with a score of: " << boards[i].calculateScore(call) << endl;
                return 0;
            }

        }
    }

    return 0;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    ifstream in(filename);
    vector<int> numbers;
    vector<Board> boards;

    string line;
    getline(in, line);
    parseNumbers(line, numbers, ',');

    int board_idx = 0;
    while(in.good()){
        getline(in, line);
        Board b = Board(board_idx);
        boards.push_back(b);

        for (int i = 0; i < 5; i++){
            getline(in, line);
            vector<int> row;
            parseNumbers(line, row, ' ');
            boards[board_idx].addRow(row);

        }
        board_idx++;
    }

    for (auto &call : numbers){
        for (auto it = boards.rbegin(); it != boards.rend(); it++){
            it->markBoard(call);
            if (it->checkIfWon()){
                if (boards.size() == 1){
                    cout << "losing board is: " << boards[0].board_idx + 1 << endl;
                    cout << "with a score of: " << boards[0].calculateScore(call) << endl;
                    return 0;
                }
                boards.erase(next(it).base());
            }
        }
    }

    return 0;
}

int main()
{
    //part1();
    part2();
}