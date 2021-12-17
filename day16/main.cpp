#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <assert.h>

using namespace std;

#if 0
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for(int i = a; i < b; i++)

struct Packet {
    int version;
    int type;
    vector<string> words;
    vector<Packet> packets;
};

class Solution {

public:
    string input;

    void addCharsToInput(char c){
        switch (c){
            case '0': input.append ("0000"); break;
            case '1': input.append ("0001"); break;
            case '2': input.append ("0010"); break;
            case '3': input.append ("0011"); break;
            case '4': input.append ("0100"); break;
            case '5': input.append ("0101"); break;
            case '6': input.append ("0110"); break;
            case '7': input.append ("0111"); break;
            case '8': input.append ("1000"); break;
            case '9': input.append ("1001"); break;
            case 'A': input.append ("1010"); break;
            case 'B': input.append ("1011"); break;
            case 'C': input.append ("1100"); break;
            case 'D': input.append ("1101"); break;
            case 'E': input.append ("1110"); break;
            case 'F': input.append ("1111"); break;
        }
    }

    void parseInput(){
        ifstream in(FILENAME);
        vector<string> hexPairs;

        string line;
        getline(in, line);

        F(i, 0, line.size())
            addCharsToInput(line[i]);

    }

    bool isOne(char c){
        return c - 48 == 1;
    }
    
    int binaryStringToInt(string &orig_str, int &i, int inc){
        string s = orig_str.substr(i, inc);
        i+= inc;
        int res = 0;
        int power = s.size() - 1;
        for(int i = 0; i < s.size(); i++){
            if (isOne(s[i])){
                res += 1 << power;
            }
            power--;
        }
        return res;
    }

    int pWordsToInt(vector<string> &words){
        string wordsCat = "";
        for(int i = 0; i < words.size(); i++){
            wordsCat.append(words[i]);
        }
        int etc = 0;
        return binaryStringToInt(wordsCat, etc, wordsCat.size());
    }

    Packet parsePacket(string s, int &i, bool align = true){
        Packet p;
        p.version = binaryStringToInt(s, i, 3);
        p.type = binaryStringToInt(s, i, 3);
        if (p.type == 4){ // This is a literal Packet
            while (i < s.size()){
                int keepGoing = binaryStringToInt(s, i, 1);
                if (keepGoing){
                    p.words.push_back(s.substr(i, 4));
                    i+=4;
                } else {
                    p.words.push_back(s.substr(i, 4));
                    i+=4;
                    break;
                }
            }
        } else { //This is an operator packet
            int pOp = binaryStringToInt(s, i, 1); 
            if (pOp == 0){ // totalLength
                int length = binaryStringToInt(s, i, 15);
                int stopIdx = i + length;

                while (i < stopIdx){
                    p.packets.push_back(parsePacket(s, i, false));
                }
            } else { // Number of following packets
                int numSubPackets = binaryStringToInt(s, i, 11);
                while (numSubPackets > 0){
                    numSubPackets--;
                    p.packets.push_back(parsePacket(s, i, false));
                }
            }
        }

        if (align){
            while (i % 8 != 0){ //remove the 0 padding
                i++;
            }
        }

        return p;
    }

    void tests(){
        int i = 0;
        Packet L = parsePacket("110100101111111000101000", i);
        cout << i << endl;
        assert(L.version == 6);
        assert(L.type == 4);
        assert(pWordsToInt(L.words) == 2021);
        
        i = 0;
        Packet twoPack = parsePacket("00111000000000000110111101000101001010010001001000000000", i);
        cout << i << endl;

        assert(twoPack.version == 1);
        assert(twoPack.type == 6);
        assert(pWordsToInt(twoPack.packets[0].words) == 10);
        assert(pWordsToInt(twoPack.packets[1].words) == 20);

        i = 0;
        Packet threePack = parsePacket("11101110000000001101010000001100100000100011000001100000", i);
        cout << i << endl;

        assert(threePack.version == 7);
        assert(threePack.type == 3);
        assert(pWordsToInt(threePack.packets[0].words) == 1);
        assert(pWordsToInt(threePack.packets[1].words) == 2);
        assert(pWordsToInt(threePack.packets[2].words) == 3);
    }

    int sumVersions(Packet p){
        int sum = 0;
        sum += p.version;

        for (auto &subPacket : p.packets){
            sum += sumVersions(subPacket);
        }
        return sum;
    }

    void solvePart1(){
        int i = 0;
        Packet p = parsePacket(input, i);

        cout << sumVersions(p) << endl;
    }

    Solution() {
        parseInput();
        //tests();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();

}