#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <math.h>

using namespace std;

#if 0
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for (int i = a; a < b; i++)

typedef long long i64;

#define OPEN -1
#define CLOSE -2
#define COMMA -3


class Solution
{

public:
    vector<i64> sn1;
    vector<i64> sn2;
    vector<vector<i64>> allNumbers;
    i64 largestMagnitude = 0;

    void parseSnailNumber(string &line, vector<i64> &sn){
        sn = {};
        for (int i = 0; i < line.size(); i++){
            switch (line[i]){
                case '[':
                    sn.push_back(OPEN);
                    break;
                case ',':
                    sn.push_back(COMMA);
                    break;
                case ']':
                    sn.push_back(CLOSE);
                    break;
                default:
                    int nextComma = line.find(',', i);
                    int nextClose = line.find(']', i);
                    if (nextComma != -1 && nextComma < nextClose){
                        sn.push_back(stoi(line.substr(i, nextComma - i)));
                        i=nextComma-1;
                    } else {
                        sn.push_back(stoi(line.substr(i, nextClose - i)));
                        i=nextClose-1;
                    }
            }
        }
    }

    void solvePart2()
    {
        ifstream in(FILENAME);

        vector<i64> num;
        string line;
        while (in.good())
        {
            getline(in, line);
            parseSnailNumber(line, num);
            allNumbers.push_back(num);

        }

        for (int i = 0; i < allNumbers.size(); i++){
            for (int j = 0; j < allNumbers.size(); j++){
                if (j != i){
                    vector<i64> sum = add(allNumbers[i], allNumbers[j]);
                    reduce(sum);
                    i64 magnitudeOfSum = magnitude(sum);
                    if (magnitudeOfSum > largestMagnitude){
                        largestMagnitude = magnitudeOfSum;
                    }
                }
            }
        }

        cout << "Largest magnitude is: " << largestMagnitude << endl;
    }

    void solvePart1()
    {
        ifstream in(FILENAME);

        string line;
        getline(in, line);
        parseSnailNumber(line, sn1);
        while (in.good())
        {
            getline(in, line);
            parseSnailNumber(line, sn2);
            sn1 = add(sn1, sn2);
            reduce(sn1);
        }

        cout << magnitude(sn1) << endl;
    }

    string SNprint(vector<i64> &sn){
        string s = "";
        for (auto &c : sn){
            switch(c){
                case OPEN:
                    s+='[';
                    break;
                case CLOSE:
                    s+=']';
                    break;
                case COMMA:
                    s+=',';
                    break;
                default:
                    s+=to_string(c);
                    break;
            }
        }
        return s;
    }

    vector<i64> add(vector<i64> sn1, vector<i64> sn2){
        vector<i64> sum = {OPEN};
        sum.insert(sum.end(), sn1.begin(), sn1.end());
        sum.push_back(COMMA);
        sum.insert(sum.end(), sn2.begin(), sn2.end());
        sum.push_back(CLOSE);
        return sum;
    }

    bool explode(vector<i64> &sn){
        int level = 0;
        for (int i = 0; i < sn.size(); i++){
            switch(sn[i]){
                case OPEN:
                    level++;
                    break;
                case CLOSE:
                    level--;
                    break;
                case COMMA:
                    break;
                default:
                    if (level > 4){
                        for (i; i < sn.size()-2; i++){
                            if (sn[i] >= 0 && sn[i+1] == COMMA && sn[i+2] >= 0){
                                for (int j = i - 1; j > 0; j--){
                                    if (sn[j] >= 0){
                                        sn[j] += sn[i];
                                        break;
                                    }
                                }
                                for (int j = i + 3; j < sn.size(); j++){
                                    if (sn[j] >= 0){
                                        sn[j] += sn[i+2];
                                        break;
                                    }
                                }
                                sn[i-1] = 0;
                                sn.erase(sn.begin() + i, sn.begin() + i + 4);
                                return true;
                            }
                        }

                    }
            }
        }
        return false;
    }

    bool split(vector<i64> &sn){
        for(int i = 0; i < sn.size(); i++){
            if (sn[i] >= 10){
                int leftNum = floor(sn[i] / 2.0);
                int rightNum = ceil(sn[i] / 2.0);
                vector<i64> newPair = {OPEN, leftNum, COMMA, rightNum, CLOSE};
                sn.erase(sn.begin() + i);
                sn.insert(sn.begin() + i, newPair.begin(), newPair.end());
                return true;
            }
        }
        return false;
    }

    void reduce(vector<i64> &sn){
        bool hasExploded = true;
        bool hasSplit = true;
        while (hasExploded || hasSplit){
            hasExploded = false;
            hasSplit = false;
            hasExploded = explode(sn);
            if (hasExploded) continue;
            hasSplit = split(sn);
        }
    }

    i64 magnitude(vector<i64> sn){
        i64 newNum = 0;
        while (sn.size() > 1){
            for (int i = 0; i < sn.size(); i++){
                if (sn[i] == OPEN && sn[i+1] >= 0 && sn[i+2] == COMMA && sn[i+3] >= 0 && sn[i+4] == CLOSE){
                    newNum = sn[i+1] * 3 + sn[i+3] * 2;
                    sn[i] = newNum;
                    sn.erase(sn.begin() + i + 1, sn.begin() + i + 5);
                    break;
                }
            }
        }
        return newNum;
    }

    void testPart1()
    {
        string exString = "[[[[[9,8],1],2],3],4]";
        parseSnailNumber(exString, sn1);
        explode(sn1);
        assert(SNprint(sn1) == "[[[[0,9],2],3],4]");

        string exString2 = "[7,[6,[5,[4,[3,2]]]]]";
        parseSnailNumber(exString2, sn1);
        explode(sn1);
        assert(SNprint(sn1) == "[7,[6,[5,[7,0]]]]");

        string exString3 = "[[6,[5,[4,[3,2]]]],1]";
        parseSnailNumber(exString3, sn1);
        explode(sn1);
        assert(SNprint(sn1) == "[[6,[5,[7,0]]],3]");

        string exString4 = "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]";
        parseSnailNumber(exString4, sn1);
        explode(sn1);
        assert(SNprint(sn1) == "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");

        string exString5 = "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]";
        parseSnailNumber(exString5, sn1);
        explode(sn1);
        assert(SNprint(sn1) == "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");


        string exString6 = "[[11,[2,[8,0]]],[9,[5,[4,[3,2]]]]]";
        parseSnailNumber(exString6, sn1);
        split(sn1);
        assert(SNprint(sn1) == "[[[5,6],[2,[8,0]]],[9,[5,[4,[3,2]]]]]");

        string exString7 = "[[[[4,3],4],4],[7,[[8,4],9]]]";
        string exString8 = "[1,1]";
        parseSnailNumber(exString7, sn1);
        parseSnailNumber(exString8, sn2);
        vector<i64> sum = add(sn1, sn2);
        assert(SNprint(sum) == "[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]");
        reduce(sum);
        assert(SNprint(sum) == "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");

        string exString9 = "[[1,2],[[3,4],5]]";
        parseSnailNumber(exString9, sn1);
        assert(magnitude(sn1) == 143);
    }

    Solution()
    {
        testPart1();
        solvePart1();
        solvePart2();
    }
};

int main()
{
    Solution *s = new Solution();
}