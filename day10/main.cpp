#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <stack>

using namespace std;

void scoreLine(string line, long &score){
    stringstream s_stream(line);
    stack<char> brackets;
    while(s_stream.good()){
        char curr = s_stream.get();
        switch (curr){
            case '(': case '[': case '{': case '<':
                brackets.push(curr);
                break;
            case ')':
                if (brackets.empty() || brackets.top() != '('){
                    score += 3;
                    return;
                } else {
                    brackets.pop();
                    break;
                }
            case ']':
                if (brackets.empty() || brackets.top() != '['){
                    score += 57;
                    return;
                } else {
                    brackets.pop();
                    break;
                }
            case '}':
                if (brackets.empty() || brackets.top() != '{'){
                    score += 1197;
                    return;
                } else {
                    brackets.pop();
                    break;
                }
            case '>':
                if (brackets.empty() || brackets.top() != '<'){
                    score += 25137;
                    return;
                } else {
                    brackets.pop();
                    break;
                }

        }
    }
}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    long score = 0;

    string line;
    while (in.good()){
        getline(in, line);
        scoreLine(line, score);
    }

    in.close();

    cout << score << endl;
    return 0;
}

void autocomplete(string line, long long &score){
    stringstream s_stream(line);
    stack<char> brackets;
    while(s_stream.good()){
        char curr = s_stream.get();
        switch (curr){
            case '(': case '[': case '{': case '<':
                brackets.push(curr);
                break;
            case ')':
                if (brackets.empty() || brackets.top() != '('){
                    score = -1;
                    return;
                } else {
                    brackets.pop();
                    break;
                }
            case ']':
                if (brackets.empty() || brackets.top() != '['){
                    score = -1;
                    return;
                } else {
                    brackets.pop();
                    break;
                }
            case '}':
                if (brackets.empty() || brackets.top() != '{'){
                    score = -1;
                    return;
                } else {
                    brackets.pop();
                    break;
                }
            case '>':
                if (brackets.empty() || brackets.top() != '<'){
                    score = -1;
                    return;
                } else {
                    brackets.pop();
                    break;
                }

        }
    }

    while (!brackets.empty()){
        char curr = brackets.top();
        brackets.pop();
        score *= 5;
        switch (curr){
            case '(':
                score += 1;
                break;
            case '[':
                score += 2;
                break;
            case '{':
                score += 3;
                break;
            case '<':
                score += 4;
                break;
        }
    }
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";

    ifstream in(filename);
    vector<long long> scores;

    string line;
    int i = 0;
    while (in.good()){
        scores.push_back({0});
        getline(in, line);
        autocomplete(line, scores[i]);
        if (scores[i] == -1){
            scores.pop_back();
        } else {
            i++;
        }
    }

    in.close();

    sort(scores.begin(), scores.end());

    cout << scores[scores.size() / 2] << endl;

    return 0;
}

int main()
{
    //part1();
    part2();
}